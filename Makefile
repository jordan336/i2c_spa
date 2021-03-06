
DIR_INCLUDE := include
DIR_SRC     := src
DIR_LINUX   := ${DIR_SRC}/linux

TGT_LINUX   := linux
TGT_LIB     := libio_spa.a

FILE_I2C_SRC := io_spa_i2c.c
FILE_SPI_SRC := io_spa_spi.c

SRCS_LINUX  := ${DIR_LINUX}/${FILE_I2C_SRC} ${DIR_LINUX}/${FILE_SPI_SRC}
OBJS_LINUX  := $(SRCS_LINUX:.c=.o)
OBJS        := ${OBJS_LINUX}

CFLAGS_DEFAULT := -Wall -Werror -std=c99 -I ${DIR_INCLUDE}


.PHONY: all clean ${TGT_LINUX}

all: ${TGT_LINUX}

%_pre: 
	$(eval PLATFORM_TGT := PLATFORM_$(shell echo $(patsubst %_pre,%,$@) | tr a-z A-Z))
	$(eval CFLAGS:=${CFLAGS_DEFAULT} -D ${PLATFORM_TGT})

${OBJS_LINUX}:| ${TGT_LINUX}_pre
${TGT_LINUX}: ${OBJS_LINUX}
	${AR} rcs ${TGT_LIB} $^

clean:
	rm -f ${OBJS}
	rm -f ${TGT_LIB}

