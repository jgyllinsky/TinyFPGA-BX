
upload: hardware.bin firmware.bin
	tinyprog -p hardware.bin -u firmware.bin

sim: hx8kdemo_tb.vvp firmware.hex
	vvp -N $<
	gtkwave testbench.vcd soc.gtkw

hx8kdemo_tb.vvp: hx8kdemo_tb.v hardware.v spimemio.v simpleuart.v picosoc.v picorv32.v spiflash.v ws2812.v
	iverilog -s testbench -o $@ $^ /usr/local/share/yosys/ice40/cells_sim.v

hardware.blif: hardware.v spimemio.v simpleuart.v picosoc.v picorv32.v ws2812.v
	yosys -ql hardware.log -p 'synth_ice40 -top hardware -blif hardware.blif' $^

hardware.asc: hardware.pcf hardware.blif
	arachne-pnr -d 8k -P cm81 -o hardware.asc -p hardware.pcf hardware.blif

hardware.bin: hardware.asc
	icetime -d hx8k -c 12 -mtr hardware.rpt hardware.asc
	icepack hardware.asc hardware.bin

firmware.hex: firmware.elf
	riscv32-unknown-elf-objcopy -O verilog firmware.elf firmware.hex

firmware.elf: sections.lds start.S firmware.c animate.c
	riscv32-unknown-elf-gcc -march=rv32imc -nostartfiles -Wl,-Bstatic,-T,sections.lds,--strip-debug,-Map=firmware.map,--cref  -ffreestanding -nostdlib -o firmware.elf start.S firmware.c animate.c

firmware.bin: firmware.elf
	riscv32-unknown-elf-objcopy -O binary firmware.elf /dev/stdout > firmware.bin


clean:
	rm -f firmware.elf firmware.hex firmware.bin firmware.o firmware.map \
	      hardware.blif hardware.log hardware.asc hardware.rpt hardware.bin




