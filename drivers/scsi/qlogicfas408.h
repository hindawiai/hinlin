<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* to be used by qlogicfas and qlogic_cs */
#अगर_अघोषित __QLOGICFAS408_H
#घोषणा __QLOGICFAS408_H

/*----------------------------------------------------------------*/
/* Configuration */

/* Set the following to max out the speed of the PIO PseuकरोDMA transfers,
   again, 0 tends to be slower, but more stable.  */

#घोषणा QL_TURBO_PDMA 1

/* This should be 1 to enable parity detection */

#घोषणा QL_ENABLE_PARITY 1

/* This will reset all devices when the driver is initialized (during bootup).
   The other linux drivers करोn't करो this, but the DOS drivers करो, and after
   using DOS or some kind of crash or lockup this will bring things back
   without requiring a cold boot.  It करोes take some समय to recover from a
   reset, so it is slower, and I have seen समयouts so that devices weren't
   recognized when this was set. */

#घोषणा QL_RESET_AT_START 0

/* crystal frequency in megahertz (क्रम offset 5 and 9)
   Please set this क्रम your card.  Most Qlogic cards are 40 Mhz.  The
   Control Concepts ISA (not VLB) is 24 Mhz */

#घोषणा XTALFREQ	40

/**********/
/* DANGER! modअगरy these at your own risk */
/* SLOWCABLE can usually be reset to zero अगर you have a clean setup and
   proper termination.  The rest are क्रम synchronous transfers and other
   advanced features अगर your device can transfer faster than 5Mb/sec.
   If you are really curious, email me क्रम a quick howto until I have
   something official */
/**********/

/*****/
/* config रेजिस्टर 1 (offset 8) options */
/* This needs to be set to 1 अगर your cabling is दीर्घ or noisy */
#घोषणा SLOWCABLE 1

/*****/
/* offset 0xc */
/* This will set fast (10Mhz) synchronous timing when set to 1
   For this to have an effect, FASTCLK must also be 1 */
#घोषणा FASTSCSI 0

/* This when set to 1 will set a faster sync transfer rate */
#घोषणा FASTCLK 0	/*(XTALFREQ>25?1:0)*/

/*****/
/* offset 6 */
/* This is the sync transfer भागisor, XTALFREQ/X will be the maximum
   achievable data rate (assuming the rest of the प्रणाली is capable
   and set properly) */
#घोषणा SYNCXFRPD 5	/*(XTALFREQ/5)*/

/*****/
/* offset 7 */
/* This is the count of how many synchronous transfers can take place
	i.e. how many reqs can occur beक्रमe an ack is given.
	The maximum value क्रम this is 15, the upper bits can modअगरy
	REQ/ACK निश्चितion and deनिश्चितion during synchronous transfers
	If this is 0, the bus will only transfer asynchronously */
#घोषणा SYNCOFFST 0
/* क्रम the curious, bits 7&6 control the deनिश्चितion delay in 1/2 cycles
	of the 40Mhz घड़ी. If FASTCLK is 1, specअगरying 01 (1/2) will
	cause the deनिश्चितion to be early by 1/2 घड़ी.  Bits 5&4 control
	the निश्चितion delay, also in 1/2 घड़ीs (FASTCLK is ignored here). */

/*----------------------------------------------------------------*/

काष्ठा qlogicfas408_priv अणु
	पूर्णांक qbase;		/* Port */
	पूर्णांक qinitid;		/* initiator ID */
	पूर्णांक qपात;		/* Flag to cause an पात */
	पूर्णांक qlirq;		/* IRQ being used */
	पूर्णांक पूर्णांक_type;		/* type of irq, 2 क्रम ISA board, 0 क्रम PCMCIA */
	अक्षर qinfo[80];		/* description */
	काष्ठा scsi_cmnd *qlcmd;	/* current command being processed */
	काष्ठा Scsi_Host *shost;	/* poपूर्णांकer back to host */
	काष्ठा qlogicfas408_priv *next; /* next निजी काष्ठा */
पूर्ण;

/* The qlogic card uses two रेजिस्टर maps - These macros select which one */
#घोषणा REG0 ( outb( inb( qbase + 0xd ) & 0x7f , qbase + 0xd ), outb( 4 , qbase + 0xd ))
#घोषणा REG1 ( outb( inb( qbase + 0xd ) | 0x80 , qbase + 0xd ), outb( 0xb4 | पूर्णांक_type, qbase + 0xd ))

/* following is watchकरोg समयout in microseconds */
#घोषणा WATCHDOG 5000000

/*----------------------------------------------------------------*/
/* the following will set the monitor border color (useful to find
   where something crashed or माला_लो stuck at and as a simple profiler) */

#घोषणा rtrc(i) अणुपूर्ण

#घोषणा get_priv_by_cmd(x) (काष्ठा qlogicfas408_priv *)&((x)->device->host->hostdata[0])
#घोषणा get_priv_by_host(x) (काष्ठा qlogicfas408_priv *)&((x)->hostdata[0])

irqवापस_t qlogicfas408_ihandl(पूर्णांक irq, व्योम *dev_id);
पूर्णांक qlogicfas408_queuecommand(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd * cmd);
पूर्णांक qlogicfas408_biosparam(काष्ठा scsi_device * disk,
			   काष्ठा block_device *dev,
			   sector_t capacity, पूर्णांक ip[]);
पूर्णांक qlogicfas408_पात(काष्ठा scsi_cmnd * cmd);
बाह्य पूर्णांक qlogicfas408_host_reset(काष्ठा scsi_cmnd *cmd);
स्थिर अक्षर *qlogicfas408_info(काष्ठा Scsi_Host *host);
पूर्णांक qlogicfas408_get_chip_type(पूर्णांक qbase, पूर्णांक पूर्णांक_type);
व्योम qlogicfas408_setup(पूर्णांक qbase, पूर्णांक id, पूर्णांक पूर्णांक_type);
पूर्णांक qlogicfas408_detect(पूर्णांक qbase, पूर्णांक पूर्णांक_type);
व्योम qlogicfas408_disable_पूर्णांकs(काष्ठा qlogicfas408_priv *priv);
#पूर्ण_अगर	/* __QLOGICFAS408_H */

