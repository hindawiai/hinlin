<शैली गुरु>
/* 
        epia.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

        epia.c is a low-level protocol driver क्रम Shuttle Technologies 
	EPIA parallel to IDE adapter chip.  This device is now obsolete
	and has been replaced with the EPAT chip, which is supported
	by epat.c, however, some devices based on EPIA are still
	available.

*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto
	1.02    GRG 1998.06.17 support older versions of EPIA

*/

#घोषणा EPIA_VERSION      "1.02"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

/* mode codes:  0  nybble पढ़ोs on port 1, 8-bit ग_लिखोs
                1  5/3 पढ़ोs on ports 1 & 2, 8-bit ग_लिखोs
                2  8-bit पढ़ोs and ग_लिखोs
                3  8-bit EPP mode
		4  16-bit EPP
		5  32-bit EPP
*/

#घोषणा j44(a,b)                (((a>>4)&0x0f)+(b&0xf0))
#घोषणा j53(a,b)                (((a>>3)&0x1f)+((b<<4)&0xe0))

/* cont =  0   IDE रेजिस्टर file
   cont =  1   IDE control रेजिस्टरs
*/

अटल पूर्णांक cont_map[2] = अणु 0, 0x80 पूर्ण;

अटल पूर्णांक epia_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक     a, b, r;

	regr += cont_map[cont];

        चयन (pi->mode)  अणु

        हाल 0: r = regr^0x39;
                w0(r); w2(1); w2(3); w0(r);
                a = r1(); w2(1); b = r1(); w2(4);
                वापस j44(a,b);

        हाल 1: r = regr^0x31;
                w0(r); w2(1); w0(r&0x37); 
                w2(3); w2(5); w0(r|0xf0);
                a = r1(); b = r2(); w2(4);
                वापस j53(a,b);

        हाल 2: r = regr^0x29;
                w0(r); w2(1); w2(0X21); w2(0x23); 
                a = r0(); w2(4);
                वापस a;

	हाल 3:
	हाल 4:
        हाल 5: w3(regr); w2(0x24); a = r4(); w2(4);
                वापस a;

        पूर्ण
        वापस -1;
पूर्ण       

अटल व्योम epia_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु       पूर्णांक  r;

	regr += cont_map[cont];

        चयन (pi->mode)  अणु

        हाल 0:
        हाल 1:
        हाल 2: r = regr^0x19;
                w0(r); w2(1); w0(val); w2(3); w2(4);
                अवरोध;

	हाल 3:
	हाल 4:
        हाल 5: r = regr^0x40;
                w3(r); w4(val); w2(4);
                अवरोध;
        पूर्ण
पूर्ण

#घोषणा WR(r,v)         epia_ग_लिखो_regr(pi,0,r,v)
#घोषणा RR(r)           (epia_पढ़ो_regr(pi,0,r))

/* The use of रेजिस्टर 0x84 is entirely unclear - it seems to control
   some EPP counters ...  currently we know about 3 dअगरferent block
   sizes:  the standard 512 byte पढ़ोs and ग_लिखोs, 12 byte ग_लिखोs and 
   2048 byte पढ़ोs (the last two being used in the CDrom drivers.
*/

अटल व्योम epia_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();

        w2(4); w0(0xa0); w0(0x50); w0(0xc0); w0(0x30); w0(0xa0); w0(0);
        w2(1); w2(4);
        अगर (pi->mode >= 3) अणु 
                w0(0xa); w2(1); w2(4); w0(0x82); w2(4); w2(0xc); w2(4);
                w2(0x24); w2(0x26); w2(4);
        पूर्ण
        WR(0x86,8);  
पूर्ण

अटल व्योम epia_disconnect ( PIA *pi )

अणु       /* WR(0x84,0x10); */
        w0(pi->saved_r0);
        w2(1); w2(4);
        w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम epia_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     k, ph, a, b;

        चयन (pi->mode) अणु

        हाल 0: w0(0x81); w2(1); w2(3); w0(0xc1);
                ph = 1;
                क्रम (k=0;k<count;k++) अणु
                        w2(2+ph); a = r1();
                        w2(4+ph); b = r1();
                        buf[k] = j44(a,b);
                        ph = 1 - ph;
                पूर्ण 
                w0(0); w2(4);
                अवरोध;

        हाल 1: w0(0x91); w2(1); w0(0x10); w2(3); 
                w0(0x51); w2(5); w0(0xd1); 
                ph = 1;
                क्रम (k=0;k<count;k++) अणु
                        w2(4+ph);
                        a = r1(); b = r2();
                        buf[k] = j53(a,b);
                        ph = 1 - ph;
                पूर्ण
                w0(0); w2(4);
                अवरोध;

        हाल 2: w0(0x89); w2(1); w2(0x23); w2(0x21); 
                ph = 1;
                क्रम (k=0;k<count;k++) अणु
                        w2(0x24+ph);
                        buf[k] = r0();
                        ph = 1 - ph;
                पूर्ण
                w2(6); w2(4);
                अवरोध;

        हाल 3: अगर (count > 512) WR(0x84,3);
		w3(0); w2(0x24);
                क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(4); WR(0x84,0);
                अवरोध;

        हाल 4: अगर (count > 512) WR(0x84,3);
		w3(0); w2(0x24);
		क्रम (k=0;k<count/2;k++) ((u16 *)buf)[k] = r4w();
                w2(4); WR(0x84,0);
                अवरोध;

        हाल 5: अगर (count > 512) WR(0x84,3);
		w3(0); w2(0x24);
                क्रम (k=0;k<count/4;k++) ((u32 *)buf)[k] = r4l();
                w2(4); WR(0x84,0);
                अवरोध;

        पूर्ण
पूर्ण

अटल व्योम epia_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     ph, k, last, d;

        चयन (pi->mode) अणु

        हाल 0:
        हाल 1:
        हाल 2: w0(0xa1); w2(1); w2(3); w2(1); w2(5);
                ph = 0;  last = 0x8000;
                क्रम (k=0;k<count;k++) अणु
                        d = buf[k];
                        अगर (d != last) अणु last = d; w0(d); पूर्ण
                        w2(4+ph);
                        ph = 1 - ph;
                पूर्ण
                w2(7); w2(4);
                अवरोध;

        हाल 3: अगर (count < 512) WR(0x84,1);
		w3(0x40);
                क्रम (k=0;k<count;k++) w4(buf[k]);
		अगर (count < 512) WR(0x84,0);
                अवरोध;

        हाल 4: अगर (count < 512) WR(0x84,1);
		w3(0x40);
                क्रम (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
		अगर (count < 512) WR(0x84,0);
                अवरोध;

        हाल 5: अगर (count < 512) WR(0x84,1);
		w3(0x40);
                क्रम (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
		अगर (count < 512) WR(0x84,0);
                अवरोध;

        पूर्ण

पूर्ण

अटल पूर्णांक epia_test_proto( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       पूर्णांक     j, k, f;
	पूर्णांक	e[2] = अणु0,0पूर्ण;

        epia_connect(pi);
        क्रम (j=0;j<2;j++) अणु
            WR(6,0xa0+j*0x10);
            क्रम (k=0;k<256;k++) अणु
                WR(2,k^0xaa);
                WR(3,k^0x55);
                अगर (RR(2) != (k^0xaa)) e[j]++;
                पूर्ण
	    WR(2,1); WR(3,1);
            पूर्ण
        epia_disconnect(pi);

        f = 0;
        epia_connect(pi);
        WR(0x84,8);
        epia_पढ़ो_block(pi,scratch,512);
        क्रम (k=0;k<256;k++) अणु
            अगर ((scratch[2*k] & 0xff) != ((k+1) & 0xff)) f++;
            अगर ((scratch[2*k+1] & 0xff) != ((-2-k) & 0xff)) f++;
        पूर्ण
        WR(0x84,0);
        epia_disconnect(pi);

        अगर (verbose)  अणु
            prपूर्णांकk("%s: epia: port 0x%x, mode %d, test=(%d,%d,%d)\n",
                   pi->device,pi->port,pi->mode,e[0],e[1],f);
        पूर्ण
        
        वापस (e[0] && e[1]) || f;

पूर्ण


अटल व्योम epia_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[6] = अणु"4-bit","5/3","8-bit",
				   "EPP-8","EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: epia %s, Shuttle EPIA at 0x%x, ",
                pi->device,EPIA_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol epia = अणु
	.owner		= THIS_MODULE,
	.name		= "epia",
	.max_mode	= 6,
	.epp_first	= 3,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= epia_ग_लिखो_regr,
	.पढ़ो_regr	= epia_पढ़ो_regr,
	.ग_लिखो_block	= epia_ग_लिखो_block,
	.पढ़ो_block	= epia_पढ़ो_block,
	.connect	= epia_connect,
	.disconnect	= epia_disconnect,
	.test_proto	= epia_test_proto,
	.log_adapter	= epia_log_adapter,
पूर्ण;

अटल पूर्णांक __init epia_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&epia);
पूर्ण

अटल व्योम __निकास epia_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&epia);
पूर्ण

MODULE_LICENSE("GPL");
module_init(epia_init)
module_निकास(epia_निकास)
