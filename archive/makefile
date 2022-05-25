# Usage:
# make			# compile final executable binary
# make run		# run executable
# make clean	# remove ALL binaries

BUILD_DIR = build/

LINKER_FLAG = -lm

WAV = wav.c

sequencer: ${WAV} sequencerPoc.c
	[ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}
	gcc  -o build/sequencer ${WAV} sequencer.c ${LINKER_FLAG}

sequencerV2: ${WAV} sequencerPocV2.c
	[ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}
	gcc  -o build/sequencerV2 ${WAV} sequencerV2.c ${LINKER_FLAG}

trimmer: ${WAV} trimmerPoc.c
	[ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}
	gcc -o build/trimmer ${WAV} trimmer.c ${LINKER_FLAG} 

run_sequencer: build/sequencer 
	./build/sequencer

run_sequencerV2: build/sequencerV2 
	./build/sequencerV2

run_trimmer: build/trimmer
	./build/trimmer

clean:
	@echo "Cleaning up..."
	rm build/*
