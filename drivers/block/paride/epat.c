<शैली गुरु>
/* 
        epat.c  (c) 1997-8  Grant R. Guenther <grant@torque.net>
                            Under the terms of the GNU General Public License.

	This is the low level protocol driver क्रम the EPAT parallel
        to IDE adapter from Shuttle Technologies.  This adapter is
        used in many popular parallel port disk products such as the
        SyQuest EZ drives, the Avatar Shark and the Imation SuperDisk.
	
*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto
        1.02    Joshua b. Jore CPP(नामd), epat_connect, epat_disconnect

*/

#घोषणा EPAT_VERSION      "1.02"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा j44(a,b)		(((a>>4)&0x0f)+(b&0xf0))
#घोषणा j53(a,b)		(((a>>3)&0x1f)+((b<<4)&0xe0))

अटल पूर्णांक epatc8;

module_param(epatc8, पूर्णांक, 0);
MODULE_PARM_DESC(epatc8, "support for the Shuttle EP1284 chip, "
	"used in any recent Imation SuperDisk (LS-120) drive.");

/* cont =  0   IDE रेजिस्टर file
   cont =  1   IDE control रेजिस्टरs
   cont =  2   पूर्णांकernal EPAT रेजिस्टरs
*/

अटल पूर्णांक cont_map[3] = अणु 0x18, 0x10, 0 पूर्ण;

अटल व्योम epat_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	पूर्णांक r;

	r = regr + cont_map[cont];

	चयन (pi->mode) अणु

	हाल 0:
	हाल 1:
	हाल 2:	w0(0x60+r); w2(1); w0(val); w2(4);
		अवरोध;

	हाल 3:
	हाल 4:
	हाल 5: w3(0x40+r); w4(val);
		अवरोध;

	पूर्ण
पूर्ण

अटल पूर्णांक epat_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक  a, b, r;

	r = regr + cont_map[cont];

	चयन (pi->mode) अणु

	हाल 0:	w0(r); w2(1); w2(3); 
		a = r1(); w2(4); b = r1();
		वापस j44(a,b);

	हाल 1: w0(0x40+r); w2(1); w2(4);
		a = r1(); b = r2(); w0(0xff);
		वापस j53(a,b);

	हाल 2: w0(0x20+r); w2(1); w2(0x25);
		a = r0(); w2(4);
		वापस a;

	हाल 3:
	हाल 4:
	हाल 5: w3(r); w2(0x24); a = r4(); w2(4);
		वापस a;

	पूर्ण
	वापस -1;	/* never माला_लो here */
पूर्ण

अटल व्योम epat_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक  k, ph, a, b;

	चयन (pi->mode) अणु

	हाल 0:	w0(7); w2(1); w2(3); w0(0xff);
		ph = 0;
		क्रम(k=0;k<count;k++) अणु
			अगर (k == count-1) w0(0xfd);
			w2(6+ph); a = r1();
			अगर (a & 8) b = a; 
			  अन्यथा अणु w2(4+ph); b = r1(); पूर्ण
			buf[k] = j44(a,b);
			ph =  1 - ph;
		पूर्ण
		w0(0); w2(4);
		अवरोध;

	हाल 1: w0(0x47); w2(1); w2(5); w0(0xff);
		ph = 0;
		क्रम(k=0;k<count;k++) अणु
			अगर (k == count-1) w0(0xfd); 
			w2(4+ph);
			a = r1(); b = r2();
			buf[k] = j53(a,b);
			ph = 1 - ph;
		पूर्ण
		w0(0); w2(4);
		अवरोध;

	हाल 2: w0(0x27); w2(1); w2(0x25); w0(0);
		ph = 0;
		क्रम(k=0;k<count-1;k++) अणु
			w2(0x24+ph);
			buf[k] = r0();
			ph = 1 - ph;
		पूर्ण
		w2(0x26); w2(0x27); buf[count-1] = r0(); 
		w2(0x25); w2(4);
		अवरोध;

	हाल 3: w3(0x80); w2(0x24);
		क्रम(k=0;k<count-1;k++) buf[k] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		अवरोध;

	हाल 4: w3(0x80); w2(0x24);
		क्रम(k=0;k<(count/2)-1;k++) ((u16 *)buf)[k] = r4w();
		buf[count-2] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		अवरोध;

	हाल 5: w3(0x80); w2(0x24);
		क्रम(k=0;k<(count/4)-1;k++) ((u32 *)buf)[k] = r4l();
		क्रम(k=count-4;k<count-1;k++) buf[k] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		अवरोध;

	पूर्ण
पूर्ण

अटल व्योम epat_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )   

अणु	पूर्णांक ph, k;

	चयन (pi->mode) अणु

	हाल 0:
	हाल 1:
	हाल 2: w0(0x67); w2(1); w2(5);
		ph = 0;
		क्रम(k=0;k<count;k++) अणु
		  	w0(buf[k]);
			w2(4+ph);
			ph = 1 - ph;
		पूर्ण
		w2(7); w2(4);
		अवरोध;

	हाल 3: w3(0xc0); 
		क्रम(k=0;k<count;k++) w4(buf[k]);
		w2(4);
		अवरोध;

	हाल 4: w3(0xc0); 
		क्रम(k=0;k<(count/2);k++) w4w(((u16 *)buf)[k]);
		w2(4);
		अवरोध;

	हाल 5: w3(0xc0); 
		क्रम(k=0;k<(count/4);k++) w4l(((u32 *)buf)[k]);
		w2(4);
		अवरोध;

	पूर्ण
पूर्ण

/* these macros access the EPAT रेजिस्टरs in native addressing */

#घोषणा	WR(r,v)		epat_ग_लिखो_regr(pi,2,r,v)
#घोषणा	RR(r)		(epat_पढ़ो_regr(pi,2,r))

/* and these access the IDE task file */

#घोषणा WRi(r,v)         epat_ग_लिखो_regr(pi,0,r,v)
#घोषणा RRi(r)           (epat_पढ़ो_regr(pi,0,r))

/* FIXME:  the CPP stuff should be fixed to handle multiple EPATs on a chain */

#घोषणा CPP(x) 	w2(4);w0(0x22);w0(0xaa);w0(0x55);w0(0);w0(0xff);\
                w0(0x87);w0(0x78);w0(x);w2(4);w2(5);w2(4);w0(0xff);

अटल व्योम epat_connect ( PIA *pi )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();

 	/* Initialize the chip */
	CPP(0);

	अगर (epatc8) अणु
		CPP(0x40);CPP(0xe0);
		w0(0);w2(1);w2(4);
		WR(0x8,0x12);WR(0xc,0x14);WR(0x12,0x10);
		WR(0xe,0xf);WR(0xf,4);
		/* WR(0xe,0xa);WR(0xf,4); */
		WR(0xe,0xd);WR(0xf,0);
		/* CPP(0x30); */
	पूर्ण

        /* Connect to the chip */
	CPP(0xe0);
        w0(0);w2(1);w2(4); /* Idle पूर्णांकo SPP */
        अगर (pi->mode >= 3) अणु
          w0(0);w2(1);w2(4);w2(0xc);
          /* Request EPP */
          w0(0x40);w2(6);w2(7);w2(4);w2(0xc);w2(4);
        पूर्ण

	अगर (!epatc8) अणु
		WR(8,0x10); WR(0xc,0x14); WR(0xa,0x38); WR(0x12,0x10);
	पूर्ण
पूर्ण

अटल व्योम epat_disconnect (PIA *pi)
अणु	CPP(0x30);
	w0(pi->saved_r0);
	w2(pi->saved_r2);
पूर्ण

अटल पूर्णांक epat_test_proto( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       पूर्णांक     k, j, f, cc;
	पूर्णांक	e[2] = अणु0,0पूर्ण;

        epat_connect(pi);
	cc = RR(0xd);
	epat_disconnect(pi);

	epat_connect(pi);
	क्रम (j=0;j<2;j++) अणु
  	    WRi(6,0xa0+j*0x10);
            क्रम (k=0;k<256;k++) अणु
                WRi(2,k^0xaa);
                WRi(3,k^0x55);
                अगर (RRi(2) != (k^0xaa)) e[j]++;
                पूर्ण
	    पूर्ण
        epat_disconnect(pi);

        f = 0;
        epat_connect(pi);
        WR(0x13,1); WR(0x13,0); WR(0xa,0x11);
        epat_पढ़ो_block(pi,scratch,512);
	
        क्रम (k=0;k<256;k++) अणु
            अगर ((scratch[2*k] & 0xff) != k) f++;
            अगर ((scratch[2*k+1] & 0xff) != (0xff-k)) f++;
        पूर्ण
        epat_disconnect(pi);

        अगर (verbose)  अणु
            prपूर्णांकk("%s: epat: port 0x%x, mode %d, ccr %x, test=(%d,%d,%d)\n",
		   pi->device,pi->port,pi->mode,cc,e[0],e[1],f);
	पूर्ण
	
        वापस (e[0] && e[1]) || f;
पूर्ण

अटल व्योम epat_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु	पूर्णांक	ver;
        अक्षर    *mode_string[6] = 
		   अणु"4-bit","5/3","8-bit","EPP-8","EPP-16","EPP-32"पूर्ण;

	epat_connect(pi);
	WR(0xa,0x38);		/* पढ़ो the version code */
        ver = RR(0xb);
        epat_disconnect(pi);

	prपूर्णांकk("%s: epat %s, Shuttle EPAT chip %x at 0x%x, ",
		pi->device,EPAT_VERSION,ver,pi->port);
	prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol epat = अणु
	.owner		= THIS_MODULE,
	.name		= "epat",
	.max_mode	= 6,
	.epp_first	= 3,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= epat_ग_लिखो_regr,
	.पढ़ो_regr	= epat_पढ़ो_regr,
	.ग_लिखो_block	= epat_ग_लिखो_block,
	.पढ़ो_block	= epat_पढ़ो_block,
	.connect	= epat_connect,
	.disconnect	= epat_disconnect,
	.test_proto	= epat_test_proto,
	.log_adapter	= epat_log_adapter,
पूर्ण;

अटल पूर्णांक __init epat_init(व्योम)
अणु
#अगर_घोषित CONFIG_PARIDE_EPATC8
	epatc8 = 1;
#पूर्ण_अगर
	वापस paride_रेजिस्टर(&epat);
पूर्ण

अटल व्योम __निकास epat_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&epat);
पूर्ण

MODULE_LICENSE("GPL");
module_init(epat_init)
module_निकास(epat_निकास)
