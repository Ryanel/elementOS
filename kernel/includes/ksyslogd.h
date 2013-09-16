/*
ksyslogd.h - Kernel - System level log daemon.
By: Corwin McKnight
*/
#ifndef KSYSLOGD_H
#define KSYSLOGD_H
#ifndef KSYSLOGD_PAYLOAD_MAGIC
#define KSYSLOGD_PAYLOAD_MAGIC 0xA1
#define MODE_PANIC 0x0
#define MODE_CRIT 0x1
#define MODE_ERROR 0x2
#define MODE_WARN 0x3
#define MODE_INFO 0x4
#define MODE_DEBUG 0x5
#define MODE_UNKN 0x6
#endif

void ksyslog_setmask(int mode);
int ksyslog(const char* title, int mode, const char* status);

typedef struct ksyslogd_payload
{
	int mode; // MODE, aka kernel, hw, driver, etc. Used for internal logging, and user controlled
	const char* title; // The title of the log entry. Aka [KERNEL]:~~~~~~~~~~~~~
	const char* payload; // The message of the entry. Aka [~~~~~~]:SYSTEM HALTED
	int ring; // The ring the cpu was in, aka kernel or user space.
	char magic; // Magic number to verify that this is an actual payload, equal to KSYSLOD_PAYLOAD_MAGIC, prevents junk from being entered in.
} ksyslogd_payload;
#endif
