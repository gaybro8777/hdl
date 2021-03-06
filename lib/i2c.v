`default_nettype none

module i2c(
	input wire clk,
	output reg scl,
	input wire sdain,
	output reg sdaout,
	
	input wire [7:0] i2caddr,
	input wire [7:0] i2cwdata,
	input wire i2creq,
	input wire i2clast,
	output reg [7:0] i2crdata,
	output reg i2cack,
	output reg i2cerr
);

	parameter QSTARTTIME = 250;
	parameter QUARTBIT = 250;

	reg [3:0] state, state_;
	localparam IDLE = 0;
	localparam START = 1;
	localparam ADDR = 2;
	localparam ADDRACK = 3;
	localparam DATA = 4;
	localparam WRDATAACK = 5;
	localparam WRWAITREQ = 6;
	localparam RDWAITREQ = 7;
	localparam RDDATAACK = 8;
	localparam RDEND = 9;
	localparam STOP = 10;
	localparam STARTREP = 11;
	
	reg [7:0] curaddr, wdata0;
	reg [7:0] sr;
	reg [15:0] timer;
	reg [2:0] ctr;
	reg starttime, bittime, clrctr, incctr, loadaddr, loaddata, shift, err_, sdaout_, last0, setrdata;
	
	initial state = IDLE;
	
	always @(posedge clk) begin
		state <= state_;
		i2cerr <= err_;
		sdaout <= sdaout_;
		if(timer > 0)
			timer <= timer - 1;
		if(starttime)
			timer <= 4*QSTARTTIME;
		if(bittime)
			timer <= 4*QUARTBIT;
		if(clrctr)
			ctr <= 0;
		if(incctr)
			ctr <= ctr + 1;
		if(loadaddr) begin
			curaddr <= i2caddr;
			wdata0 <= i2cwdata;
			last0 <= i2clast;
			sr <= i2caddr;
		end
		if(loaddata && !curaddr[0])
			sr <= loadaddr ? i2cwdata : wdata0;
		if(setrdata)
			i2crdata <= sr;
		if(shift)
			sr <= {sr[6:0], sdain};
	end
	
	always @(*) begin
		state_ = state;
		err_ = i2cerr;
		scl = 1;
		starttime = 0;
		bittime = 0;
		i2cack = 0;
		clrctr = 0;
		incctr = 0;
		loadaddr = 0;
		loaddata = 0;
		shift = 0;
		setrdata = 0;
		sdaout_ = sdaout;
		case(state)
		IDLE: begin
			sdaout_ = 1;
			if(i2creq) begin
				loadaddr = 1;
				err_ = 0;
				state_ = START;
				starttime = 1;
			end
		end
		START: begin
			if(timer == 2*QSTARTTIME)
				sdaout_ = 0;
			if(timer == 0) begin
				state_ = ADDR;
				clrctr = 1;
				bittime = 1;
			end
		end
		ADDR: begin
			shift = timer == 3*QUARTBIT;
			if(shift)
				sdaout_ = sr[7];
			scl = timer < 2*QUARTBIT;
			if(timer == 0) begin
				if(ctr == 7)
					state_ = ADDRACK;
				incctr = 1;
				bittime = 1;
			end
		end
		ADDRACK: begin
			if(timer == 3*QUARTBIT)
				sdaout_ = 1;
			scl = timer < 2*QUARTBIT;
			if(timer == 0) begin
				if(sdain) begin
					starttime = 1;
					state_ = STOP;
					err_ = 1;
				end else begin
					state_ = DATA;
					loaddata = 1;
					bittime = 1;
				end
			end
		end
		DATA: begin
			scl = timer < 2*QUARTBIT;
			if(curaddr[0]) begin
				shift = timer == QUARTBIT;
				if(timer == 3*QUARTBIT)
					sdaout_ = 1;
			end else begin
				shift = timer == 3*QUARTBIT;
				if(shift)
					sdaout_ = sr[7];
			end
			if(timer == 0) begin
				bittime = 1;
				incctr = 1;
				if(ctr == 7)
					if(!curaddr[0])
						state_ = WRDATAACK;
					else begin
						setrdata = 1;	
						if(last0)
							state_ = RDEND;
						else begin
							i2cack = 1;
							bittime = 0;
							state_ = RDWAITREQ;
						end
					end
			end 
		end
		WRDATAACK: begin
			scl = timer < 2*QUARTBIT;
			if(timer == 3 * QUARTBIT)
				sdaout_ = 1;
			if(timer == 0) begin
				if(sdain || last0) begin
					err_ = sdain;
					starttime = 1;
					state_ = STOP;
				end else begin
					i2cack = 1;
					state_ = WRWAITREQ;
				end
			end
		end
		WRWAITREQ:
			if(i2creq) begin
				loadaddr = 1;
				if(i2caddr != curaddr) begin
					starttime = 1;
					state_ = STARTREP;
				end else begin
					bittime = 1;
					loaddata = 1;
					state_ = DATA;
				end
			end
		RDWAITREQ:
			if(i2creq) begin
				loadaddr = 1;
				bittime = 1;
				state_ = RDDATAACK;
			end
		RDDATAACK: begin
			scl = timer < 2*QUARTBIT;
			if(timer == 3 * QUARTBIT)
				sdaout_ = i2caddr != curaddr;
			if(timer == 0) begin
				if(i2caddr != curaddr) begin
					starttime = 1;
					state_ = STARTREP;
				end else begin
					bittime = 1;
					state_ = DATA;
				end
			end
		end
		RDEND: begin
			scl = timer < 2*QUARTBIT;
			if(timer == 3 * QUARTBIT)
				sdaout_ = 1;
			if(timer == 0) begin
				starttime = 1;
				state_ = STOP;
			end
		end
		STOP: begin
			scl = timer < 2 * QSTARTTIME;
			if(timer == 3*QSTARTTIME)
				sdaout_ = 0;
			if(timer == QSTARTTIME)
				sdaout_ = 1;
			if(timer == 0) begin
				i2cack = 1;
				state_ = IDLE;
			end
		end
		STARTREP: begin
			scl = timer < 2 * QSTARTTIME;
			if(timer == 3*QSTARTTIME)
				sdaout_ = 1;
			if(timer == QSTARTTIME)
				sdaout_ = 0;
			if(timer == 0) begin
				state_ = ADDR;
				clrctr = 1;
				bittime = 1;
			end
		end
		endcase
	end
endmodule
