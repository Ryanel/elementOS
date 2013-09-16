/*
ksyslogd.c - Kernel - System level log daemon.
By: Corwin McKnight
*/
#include <ksyslogd.h>
#include <stdio.h>
#include <textmode.h>

int mask=MODE_UNKN;

//TODO: Make Usefull by actually logging input.
ksyslogd_payload ksyslog_renderpayload(int mode, const char* title, const char* status)
{
	ksyslogd_payload payload;

	payload.mode    = mode;
	payload.title   = title;
	payload.payload = status;
	payload.ring    = 0; //TODO: Get current ring from OS. Right now just have set as 0 (AKA KERNEL)
	payload.magic = KSYSLOGD_PAYLOAD_MAGIC;
}

void ksyslog_setmask(int mode)
{
	mask=mode;
}

int ksyslog(const char* title, int mode, const char* status)
{
	//ksyslog_renderpayload(mode, title, status);
	//REPLACE WITH PRINTFUCTION
	//TODO: Replace ???? With mode or color.
	if(mode<=mask)
	{
		switch(mode)
		{
			case MODE_PANIC:
				tm_setAttribute(0x0C);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			case MODE_CRIT:
				tm_setAttribute(0x0D);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			case MODE_ERROR:
				tm_setAttribute(0x04);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			case MODE_WARN:
				tm_setAttribute(0x0E);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			case MODE_INFO:
				tm_setAttribute(0x09);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			case MODE_DEBUG:
				tm_setAttribute(0x01);
				printf("[%s]:%s\n",title,status);
				tm_setAttribute(0x0F);
				break;
			default:
				printf("[%s]:%s\n",title,status);
		}

	}

}
