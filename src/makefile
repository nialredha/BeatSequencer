# Usage:
# make			# compile final executable binary
# make run		# run executable
# make clean	# remove ALL binaries

BUILD_DIR = ../build/

LINKER_FLAG = -lm

WAV = wav.c
FFT = fft.c
FIL = filters.c
SEQ = sequencer.c
COM = complex.c

sequencer: ${WAV} ${SEQ} main.c
	[ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}
	gcc  -o ../build/sequencer ${WAV} ${FFT} ${FIL} ${SEQ} ${COM} main.c ${LINKER_FLAG}

sequencerRes: ${WAV} sequencer_res.c main.c
	[ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}
	gcc  -o ../build/sequencerRes ${WAV} ${FFT} ${FIL} sequencer_res.c ${COM} main.c ${LINKER_FLAG}

run:
	./../build/sequencer

runRes:
	./../build/sequencerRes

clean:
	@echo "Cleaning up..."
	rm ../build/*
