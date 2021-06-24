<शैली गुरु>
#अगर_अघोषित __DRIVERS_PARIDE_H__
#घोषणा __DRIVERS_PARIDE_H__

/* 
	paride.h	(c) 1997-8  Grant R. Guenther <grant@torque.net>
   		                    Under the terms of the GPL.

   This file defines the पूर्णांकerface between the high-level parallel
   IDE device drivers (pd, pf, pcd, pt) and the adapter chips.

*/

/* Changes:

	1.01	GRG 1998.05.05	init_proto, release_proto
*/

#घोषणा PARIDE_H_VERSION 	"1.01"

/* Some adapters need to know what kind of device they are in

   Values क्रम devtype:
*/

#घोषणा	PI_PD	0	/* IDE disk */
#घोषणा PI_PCD	1	/* ATAPI CDrom */
#घोषणा PI_PF   2	/* ATAPI disk */
#घोषणा PI_PT	3	/* ATAPI tape */
#घोषणा PI_PG   4       /* ATAPI generic */

/* The paride module contains no state, instead the drivers allocate
   a pi_adapter data काष्ठाure and pass it to paride in every operation.

*/

काष्ठा pi_adapter  अणु

	काष्ठा pi_protocol *proto;   /* adapter protocol */
	पूर्णांक	port;		     /* base address of parallel port */
	पूर्णांक	mode;		     /* transfer mode in use */
	पूर्णांक     delay;		     /* adapter delay setting */
	पूर्णांक	devtype;	     /* device type: PI_PD etc. */
	अक्षर    *device;	     /* name of driver */
	पूर्णांक     unit;		     /* unit number क्रम chained adapters */
	पूर्णांक	saved_r0;	     /* saved port state */
	पूर्णांक	saved_r2;	     /* saved port state */
	पूर्णांक	reserved;	     /* number of ports reserved */
	अचिन्हित दीर्घ	निजी;     /* क्रम protocol module */

	रुको_queue_head_t parq;     /* semaphore क्रम parport sharing */
	व्योम	*pardev;	     /* poपूर्णांकer to pardevice */
	अक्षर	*parname;	     /* parport name */
	पूर्णांक	claimed;	     /* parport has alपढ़ोy been claimed */
	व्योम (*claim_cont)(व्योम);    /* continuation क्रम parport रुको */
पूर्ण;

प्रकार काष्ठा pi_adapter PIA;

/* functions exported by paride to the high level drivers */

बाह्य पूर्णांक pi_init(PIA *pi, 
	पूर्णांक स्वतःprobe,		/* 1 to स्वतःprobe */
	पूर्णांक port, 		/* base port address */
	पूर्णांक mode, 		/* -1 क्रम स्वतःprobe */
	पूर्णांक unit,		/* unit number, अगर supported */
	पूर्णांक protocol, 		/* protocol to use */
	पूर्णांक delay, 		/* -1 to use adapter specअगरic शेष */
	अक्षर * scratch, 	/* address of 512 byte buffer */
	पूर्णांक devtype,		/* device type: PI_PD, PI_PCD, etc ... */
	पूर्णांक verbose,		/* log verbose data जबतक probing */
	अक्षर *device		/* name of the driver */
	);			/* वापसs 0 on failure, 1 on success */

बाह्य व्योम pi_release(PIA *pi);

/* रेजिस्टरs are addressed as (cont,regr)

       	cont: 0 क्रम command रेजिस्टर file, 1 क्रम control रेजिस्टर(s)
	regr: 0-7 क्रम रेजिस्टर number.

*/

बाह्य व्योम pi_ग_लिखो_regr(PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val);

बाह्य पूर्णांक pi_पढ़ो_regr(PIA *pi, पूर्णांक cont, पूर्णांक regr);

बाह्य व्योम pi_ग_लिखो_block(PIA *pi, अक्षर * buf, पूर्णांक count);

बाह्य व्योम pi_पढ़ो_block(PIA *pi, अक्षर * buf, पूर्णांक count);

बाह्य व्योम pi_connect(PIA *pi);

बाह्य व्योम pi_disconnect(PIA *pi);

बाह्य व्योम pi_करो_claimed(PIA *pi, व्योम (*cont)(व्योम));
बाह्य पूर्णांक pi_schedule_claimed(PIA *pi, व्योम (*cont)(व्योम));

/* macros and functions exported to the protocol modules */

#घोषणा delay_p			(pi->delay?udelay(pi->delay):(व्योम)0)
#घोषणा out_p(offs,byte)	outb(byte,pi->port+offs); delay_p;
#घोषणा in_p(offs)		(delay_p,inb(pi->port+offs))

#घोषणा w0(byte)                अणुout_p(0,byte);पूर्ण
#घोषणा r0()                    (in_p(0) & 0xff)
#घोषणा w1(byte)                अणुout_p(1,byte);पूर्ण
#घोषणा r1()                    (in_p(1) & 0xff)
#घोषणा w2(byte)                अणुout_p(2,byte);पूर्ण
#घोषणा r2()                    (in_p(2) & 0xff)
#घोषणा w3(byte)                अणुout_p(3,byte);पूर्ण
#घोषणा w4(byte)                अणुout_p(4,byte);पूर्ण
#घोषणा r4()                    (in_p(4) & 0xff)
#घोषणा w4w(data)     		अणुoutw(data,pi->port+4); delay_p;पूर्ण
#घोषणा w4l(data)     		अणुoutl(data,pi->port+4); delay_p;पूर्ण
#घोषणा r4w()         		(delay_p,inw(pi->port+4)&0xffff)
#घोषणा r4l()         		(delay_p,inl(pi->port+4)&0xffffffff)

अटल अंतरभूत u16 pi_swab16( अक्षर *b, पूर्णांक k)

अणु 	जोड़ अणु u16 u; अक्षर t[2]; पूर्ण r;

	r.t[0]=b[2*k+1]; r.t[1]=b[2*k];
        वापस r.u;
पूर्ण

अटल अंतरभूत u32 pi_swab32( अक्षर *b, पूर्णांक k)

अणु 	जोड़ अणु u32 u; अक्षर f[4]; पूर्ण r;

	r.f[0]=b[4*k+1]; r.f[1]=b[4*k];
	r.f[2]=b[4*k+3]; r.f[3]=b[4*k+2];
        वापस r.u;
पूर्ण

काष्ठा pi_protocol अणु

	अक्षर	name[8];	/* name क्रम this protocol */
	पूर्णांक	index;		/* index पूर्णांकo protocol table */

	पूर्णांक	max_mode;	/* max mode number */
	पूर्णांक	epp_first;	/* modes >= this use 8 ports */
	
	पूर्णांक	शेष_delay;  /* delay parameter अगर not specअगरied */
	पूर्णांक	max_units;	/* max chained units probed क्रम */

	व्योम (*ग_लिखो_regr)(PIA *,पूर्णांक,पूर्णांक,पूर्णांक);
	पूर्णांक  (*पढ़ो_regr)(PIA *,पूर्णांक,पूर्णांक);
	व्योम (*ग_लिखो_block)(PIA *,अक्षर *,पूर्णांक);
	व्योम (*पढ़ो_block)(PIA *,अक्षर *,पूर्णांक);

	व्योम (*connect)(PIA *);
	व्योम (*disconnect)(PIA *);
	
	पूर्णांक  (*test_port)(PIA *);
	पूर्णांक  (*probe_unit)(PIA *);
	पूर्णांक  (*test_proto)(PIA *,अक्षर *,पूर्णांक);
	व्योम (*log_adapter)(PIA *,अक्षर *,पूर्णांक);
	
	पूर्णांक (*init_proto)(PIA *);
	व्योम (*release_proto)(PIA *);
	काष्ठा module *owner;
पूर्ण;

प्रकार काष्ठा pi_protocol PIP;

बाह्य पूर्णांक paride_रेजिस्टर( PIP * );
बाह्य व्योम paride_unरेजिस्टर ( PIP * );
व्योम *pi_रेजिस्टर_driver(अक्षर *);
व्योम pi_unरेजिस्टर_driver(व्योम *);

#पूर्ण_अगर /* __DRIVERS_PARIDE_H__ */
/* end of paride.h */
