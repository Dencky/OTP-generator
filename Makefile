CC = gcc
CFLAGS = -Wall -Wextra -O2 -pedantic
LDFLAGS = -lcrypto -lm
TARGET = otp-generator

SRCS = src/otp-generator.c src/hotp.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

otp-generator.o: otp-generator.c otp-generator.h hotp.h
hotp.o: hotp.c hotp.h

clean:
	rm -f $(OBJS) $(TARGET)