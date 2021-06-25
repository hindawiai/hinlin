<शैली गुरु>
/* 
        on26.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

        on26.c is a low-level protocol driver क्रम the 
        OnSpec 90c26 parallel to IDE adapter chip.

*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto
	1.02    GRG 1998.09.23 updates क्रम the -E rev chip
	1.03    GRG 1998.12.14 fix क्रम slave drives
	1.04    GRG 1998.12.20 yet another bug fix

*/

#घोषणा ON26_VERSION      "1.04"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

/* mode codes:  0  nybble पढ़ोs, 8-bit ग_लिखोs
                1  8-bit पढ़ोs and ग_लिखोs
                2  8-bit EPP mode
		3  EPP-16
		4  EPP-32
*/

#घोषणा j44(a,b)  (((a>>4)&0x0f)|(b&0xf0))

#घोषणा P1	w2(5);w2(0xd);w2(5);w2(0xd);w2(5);w2(4);
#घोषणा P2	w2(5);w2(7);w2(5);w2(4);

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक on26_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक     a, b, r;

	r = (regr<<2) + 1 + cont;

        चयन (pi->mode)  अणु

        हाल 0: w0(1); P1; w0(r); P2; w0(0); P1; 
		w2(6); a = r1(); w2(4);
		w2(6); b = r1(); w2(4);
		w2(6); w2(4); w2(6); w2(4);
                वापस j44(a,b);

        हाल 1: w0(1); P1; w0(r); P2; w0(0); P1;
		w2(0x26); a = r0(); w2(4); w2(0x26); w2(4);
                वापस a;

	हाल 2:
	हाल 3:
        हाल 4: w3(1); w3(1); w2(5); w4(r); w2(4);
		w3(0); w3(0); w2(0x24); a = r4(); w2(4);
		w2(0x24); (व्योम)r4(); w2(4);
                वापस a;

        पूर्ण
        वापस -1;
पूर्ण       

अटल व्योम on26_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val )

अणु       पूर्णांक  r;

        r = (regr<<2) + 1 + cont;

        चयन (pi->mode)  अणु

        हाल 0:
        हाल 1: w0(1); P1; w0(r); P2; w0(0); P1;
		w0(val); P2; w0(val); P2;
		अवरोध;

	हाल 2:
	हाल 3:
        हाल 4: w3(1); w3(1); w2(5); w4(r); w2(4);
		w3(0); w3(0); 
		w2(5); w4(val); w2(4);
		w2(5); w4(val); w2(4);
                अवरोध;
        पूर्ण
पूर्ण

#घोषणा  CCP(x)  w0(0xfe);w0(0xaa);w0(0x55);w0(0);w0(0xff);\
		 w0(0x87);w0(0x78);w0(x);w2(4);w2(5);w2(4);w0(0xff);

अटल व्योम on26_connect ( PIA *pi )

अणु       पूर्णांक	x;

	pi->saved_r0 = r0();
        pi->saved_r2 = r2();

        CCP(0x20);
	x = 8; अगर (pi->mode) x = 9;

	w0(2); P1; w0(8); P2;
	w0(2); P1; w0(x); P2;
पूर्ण

अटल व्योम on26_disconnect ( PIA *pi )

अणु       अगर (pi->mode >= 2) अणु w3(4); w3(4); w3(4); w3(4); पूर्ण
	              अन्यथा अणु w0(4); P1; w0(4); P1; पूर्ण
	CCP(0x30);
        w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

#घोषणा	RESET_WAIT  200

अटल पूर्णांक on26_test_port( PIA *pi)  /* hard reset */

अणु       पूर्णांक     i, m, d, x=0, y=0;

        pi->saved_r0 = r0();
        pi->saved_r2 = r2();

        d = pi->delay;
        m = pi->mode;
        pi->delay = 5;
        pi->mode = 0;

        w2(0xc);

        CCP(0x30); CCP(0); 

        w0(0xfe);w0(0xaa);w0(0x55);w0(0);w0(0xff);
        i = ((r1() & 0xf0) << 4); w0(0x87);
        i |= (r1() & 0xf0); w0(0x78);
        w0(0x20);w2(4);w2(5);
        i |= ((r1() & 0xf0) >> 4);
        w2(4);w0(0xff);

        अगर (i == 0xb5f) अणु

            w0(2); P1; w0(0);   P2;
            w0(3); P1; w0(0);   P2;
            w0(2); P1; w0(8);   P2; udelay(100);
            w0(2); P1; w0(0xa); P2; udelay(100);
            w0(2); P1; w0(8);   P2; udelay(1000);
            
            on26_ग_लिखो_regr(pi,0,6,0xa0);

            क्रम (i=0;i<RESET_WAIT;i++) अणु
                on26_ग_लिखो_regr(pi,0,6,0xa0);
                x = on26_पढ़ो_regr(pi,0,7);
                on26_ग_लिखो_regr(pi,0,6,0xb0);
                y = on26_पढ़ो_regr(pi,0,7);
                अगर (!((x&0x80)||(y&0x80))) अवरोध;
                mdelay(100);
            पूर्ण

	    अगर (i == RESET_WAIT) 
		prपूर्णांकk("on26: Device reset failed (%x,%x)\n",x,y);

            w0(4); P1; w0(4); P1;
        पूर्ण

        CCP(0x30);

        pi->delay = d;
        pi->mode = m;
        w0(pi->saved_r0);
        w2(pi->saved_r2);

        वापस 5;
पूर्ण


अटल व्योम on26_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     k, a, b;

        चयन (pi->mode) अणु

        हाल 0: w0(1); P1; w0(1); P2; w0(2); P1; w0(0x18); P2; w0(0); P1;
		udelay(10);
		क्रम (k=0;k<count;k++) अणु
                        w2(6); a = r1();
                        w2(4); b = r1();
                        buf[k] = j44(a,b);
                पूर्ण
		w0(2); P1; w0(8); P2; 
                अवरोध;

        हाल 1: w0(1); P1; w0(1); P2; w0(2); P1; w0(0x19); P2; w0(0); P1;
		udelay(10);
                क्रम (k=0;k<count/2;k++) अणु
                        w2(0x26); buf[2*k] = r0();  
			w2(0x24); buf[2*k+1] = r0();
                पूर्ण
                w0(2); P1; w0(9); P2;
                अवरोध;

        हाल 2: w3(1); w3(1); w2(5); w4(1); w2(4);
		w3(0); w3(0); w2(0x24);
		udelay(10);
                क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(4);
                अवरोध;

        हाल 3: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0x24);
                udelay(10);
                क्रम (k=0;k<count/2;k++) ((u16 *)buf)[k] = r4w();
                w2(4);
                अवरोध;

        हाल 4: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0x24);
                udelay(10);
                क्रम (k=0;k<count/4;k++) ((u32 *)buf)[k] = r4l();
                w2(4);
                अवरोध;

        पूर्ण
पूर्ण

अटल व्योम on26_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक	k;

        चयन (pi->mode) अणु

        हाल 0: 
        हाल 1: w0(1); P1; w0(1); P2; 
		w0(2); P1; w0(0x18+pi->mode); P2; w0(0); P1;
		udelay(10);
		क्रम (k=0;k<count/2;k++) अणु
                        w2(5); w0(buf[2*k]); 
			w2(7); w0(buf[2*k+1]);
                पूर्ण
                w2(5); w2(4);
		w0(2); P1; w0(8+pi->mode); P2;
                अवरोध;

        हाल 2: w3(1); w3(1); w2(5); w4(1); w2(4);
		w3(0); w3(0); w2(0xc5);
		udelay(10);
                क्रम (k=0;k<count;k++) w4(buf[k]);
		w2(0xc4);
                अवरोध;

        हाल 3: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0xc5);
                udelay(10);
                क्रम (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(0xc4);
                अवरोध;

        हाल 4: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0xc5);
                udelay(10);
                क्रम (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(0xc4);
                अवरोध;

        पूर्ण

पूर्ण

अटल व्योम on26_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[5] = अणु"4-bit","8-bit","EPP-8",
				   "EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: on26 %s, OnSpec 90c26 at 0x%x, ",
                pi->device,ON26_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol on26 = अणु
	.owner		= THIS_MODULE,
	.name		= "on26",
	.max_mode	= 5,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= on26_ग_लिखो_regr,
	.पढ़ो_regr	= on26_पढ़ो_regr,
	.ग_लिखो_block	= on26_ग_लिखो_block,
	.पढ़ो_block	= on26_पढ़ो_block,
	.connect	= on26_connect,
	.disconnect	= on26_disconnect,
	.test_port	= on26_test_port,
	.log_adapter	= on26_log_adapter,
पूर्ण;

अटल पूर्णांक __init on26_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&on26);
पूर्ण

अटल व्योम __निकास on26_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&on26);
पूर्ण

MODULE_LICENSE("GPL");
module_init(on26_init)
module_निकास(on26_निकास)
