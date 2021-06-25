<शैली गुरु>
/* 
	bpck.c	(c) 1996-8  Grant R. Guenther <grant@torque.net>
		            Under the terms of the GNU General Public License.

	bpck.c is a low-level protocol driver क्रम the MicroSolutions 
	"backpack" parallel port IDE adapter.  

*/

/* Changes:

	1.01	GRG 1998.05.05 init_proto, release_proto, pi->delay 
	1.02    GRG 1998.08.15 शेष pi->delay वापसed to 4

*/

#घोषणा	BPCK_VERSION	"1.02" 

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#अघोषित r2
#अघोषित w2

#घोषणा PC			pi->निजी
#घोषणा r2()			(PC=(in_p(2) & 0xff))
#घोषणा w2(byte)  		अणुout_p(2,byte); PC = byte;पूर्ण
#घोषणा t2(pat)   		अणुPC ^= pat; out_p(2,PC);पूर्ण
#घोषणा e2()			अणुPC &= 0xfe; out_p(2,PC);पूर्ण
#घोषणा o2()			अणुPC |= 1; out_p(2,PC);पूर्ण

#घोषणा j44(l,h)     (((l>>3)&0x7)|((l>>4)&0x8)|((h<<1)&0x70)|(h&0x80))

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
   cont = 2 - use पूर्णांकernal bpck रेजिस्टर addressing
*/

अटल पूर्णांक  cont_map[3] = अणु 0x40, 0x48, 0 पूर्ण;

अटल पूर्णांक bpck_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक r, l, h;

	r = regr + cont_map[cont];

	चयन (pi->mode) अणु

	हाल 0: w0(r & 0xf); w0(r); t2(2); t2(4);
	        l = r1();
        	t2(4);
        	h = r1();
        	वापस j44(l,h);

	हाल 1: w0(r & 0xf); w0(r); t2(2);
	        e2(); t2(0x20);
		t2(4); h = r0();
	        t2(1); t2(0x20);
	        वापस h;

	हाल 2:
	हाल 3:
	हाल 4: w0(r); w2(9); w2(0); w2(0x20);
		h = r4();
		w2(0);
		वापस h;

	पूर्ण
	वापस -1;
पूर्ण	

अटल व्योम bpck_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val )

अणु	पूर्णांक	r;

        r = regr + cont_map[cont];

	चयन (pi->mode) अणु

	हाल 0:
	हाल 1: w0(r);
		t2(2);
		w0(val);
		o2(); t2(4); t2(1);
		अवरोध;

	हाल 2:
	हाल 3:
	हाल 4: w0(r); w2(9); w2(0);
		w0(val); w2(1); w2(3); w2(0);
		अवरोध;

	पूर्ण
पूर्ण

/* These macros access the bpck रेजिस्टरs in native addressing */

#घोषणा WR(r,v)		bpck_ग_लिखो_regr(pi,2,r,v)
#घोषणा RR(r)		(bpck_पढ़ो_regr(pi,2,r))

अटल व्योम bpck_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक i;

	चयन (pi->mode) अणु

	हाल 0: WR(4,0x40);
		w0(0x40); t2(2); t2(1);
		क्रम (i=0;i<count;i++) अणु w0(buf[i]); t2(4); पूर्ण
		WR(4,0);
		अवरोध;

	हाल 1: WR(4,0x50);
                w0(0x40); t2(2); t2(1);
                क्रम (i=0;i<count;i++) अणु w0(buf[i]); t2(4); पूर्ण
                WR(4,0x10);
		अवरोध;

	हाल 2: WR(4,0x48);
		w0(0x40); w2(9); w2(0); w2(1);
		क्रम (i=0;i<count;i++) w4(buf[i]);
		w2(0);
		WR(4,8);
		अवरोध;

        हाल 3: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(1);
                क्रम (i=0;i<count/2;i++) w4w(((u16 *)buf)[i]);
                w2(0);
                WR(4,8);
                अवरोध;
 
        हाल 4: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(1);
                क्रम (i=0;i<count/4;i++) w4l(((u32 *)buf)[i]);
                w2(0);
                WR(4,8);
                अवरोध;
 	पूर्ण
पूर्ण

अटल व्योम bpck_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक i, l, h;

	चयन (pi->mode) अणु

      	हाल 0: WR(4,0x40);
		w0(0x40); t2(2);
		क्रम (i=0;i<count;i++) अणु
		    t2(4); l = r1();
		    t2(4); h = r1();
		    buf[i] = j44(l,h);
		पूर्ण
		WR(4,0);
		अवरोध;

	हाल 1: WR(4,0x50);
		w0(0x40); t2(2); t2(0x20);
      	        क्रम(i=0;i<count;i++) अणु t2(4); buf[i] = r0(); पूर्ण
	        t2(1); t2(0x20);
	        WR(4,0x10);
		अवरोध;

	हाल 2: WR(4,0x48);
		w0(0x40); w2(9); w2(0); w2(0x20);
		क्रम (i=0;i<count;i++) buf[i] = r4();
		w2(0);
		WR(4,8);
		अवरोध;

        हाल 3: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(0x20);
                क्रम (i=0;i<count/2;i++) ((u16 *)buf)[i] = r4w();
                w2(0);
                WR(4,8);
                अवरोध;

        हाल 4: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(0x20);
                क्रम (i=0;i<count/4;i++) ((u32 *)buf)[i] = r4l();
                w2(0);
                WR(4,8);
                अवरोध;

	पूर्ण
पूर्ण

अटल पूर्णांक bpck_probe_unit ( PIA *pi )

अणु	पूर्णांक o1, o0, f7, id;
	पूर्णांक t, s;

	id = pi->unit;
	s = 0;
	w2(4); w2(0xe); r2(); t2(2); 
	o1 = r1()&0xf8;
	o0 = r0();
	w0(255-id); w2(4); w0(id);
	t2(8); t2(8); t2(8);
	t2(2); t = r1()&0xf8;
	f7 = ((id % 8) == 7);
	अगर ((f7) || (t != o1)) अणु t2(2); s = r1()&0xf8; पूर्ण
	अगर ((t == o1) && ((!f7) || (s == o1)))  अणु
		w2(0x4c); w0(o0);
		वापस 0;	
	पूर्ण
	t2(8); w0(0); t2(2); w2(0x4c); w0(o0);
	वापस 1;
पूर्ण
	
अटल व्योम bpck_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
	w0(0xff-pi->unit); w2(4); w0(pi->unit);
	t2(8); t2(8); t2(8); 
	t2(2); t2(2);
	
	चयन (pi->mode) अणु

	हाल 0: t2(8); WR(4,0);
		अवरोध;

	हाल 1: t2(8); WR(4,0x10);
		अवरोध;

	हाल 2:
        हाल 3:
	हाल 4: w2(0); WR(4,8);
		अवरोध;

	पूर्ण

	WR(5,8);

	अगर (pi->devtype == PI_PCD) अणु
		WR(0x46,0x10);		/* fiddle with ESS logic ??? */
		WR(0x4c,0x38);
		WR(0x4d,0x88);
		WR(0x46,0xa0);
		WR(0x41,0);
		WR(0x4e,8);
		पूर्ण
पूर्ण

अटल व्योम bpck_disconnect ( PIA *pi )

अणु	w0(0); 
	अगर (pi->mode >= 2) अणु w2(9); w2(0); पूर्ण अन्यथा t2(2);
	w2(0x4c); w0(pi->saved_r0);
पूर्ण 

अटल व्योम bpck_क्रमce_spp ( PIA *pi )

/* This fakes the EPP protocol to turn off EPP ... */

अणु       pi->saved_r0 = r0();
        w0(0xff-pi->unit); w2(4); w0(pi->unit);
        t2(8); t2(8); t2(8); 
        t2(2); t2(2);

        w2(0); 
        w0(4); w2(9); w2(0); 
        w0(0); w2(1); w2(3); w2(0);     
        w0(0); w2(9); w2(0);
        w2(0x4c); w0(pi->saved_r0);
पूर्ण

#घोषणा TEST_LEN  16

अटल पूर्णांक bpck_test_proto( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु	पूर्णांक i, e, l, h, om;
	अक्षर buf[TEST_LEN];

	bpck_क्रमce_spp(pi);

	चयन (pi->mode) अणु

	हाल 0: bpck_connect(pi);
		WR(0x13,0x7f);
		w0(0x13); t2(2);
		क्रम(i=0;i<TEST_LEN;i++) अणु
                    t2(4); l = r1();
                    t2(4); h = r1();
                    buf[i] = j44(l,h);
		पूर्ण
		bpck_disconnect(pi);
		अवरोध;

        हाल 1: bpck_connect(pi);
		WR(0x13,0x7f);
                w0(0x13); t2(2); t2(0x20);
                क्रम(i=0;i<TEST_LEN;i++) अणु t2(4); buf[i] = r0(); पूर्ण
                t2(1); t2(0x20);
		bpck_disconnect(pi);
		अवरोध;

	हाल 2:
	हाल 3:
	हाल 4: om = pi->mode;
		pi->mode = 0;
		bpck_connect(pi);
		WR(7,3);
		WR(4,8);
		bpck_disconnect(pi);

		pi->mode = om;
		bpck_connect(pi);
		w0(0x13); w2(9); w2(1); w0(0); w2(3); w2(0); w2(0xe0);

		चयन (pi->mode) अणु
		  हाल 2: क्रम (i=0;i<TEST_LEN;i++) buf[i] = r4();
			  अवरोध;
		  हाल 3: क्रम (i=0;i<TEST_LEN/2;i++) ((u16 *)buf)[i] = r4w();
                          अवरोध;
		  हाल 4: क्रम (i=0;i<TEST_LEN/4;i++) ((u32 *)buf)[i] = r4l();
                          अवरोध;
		पूर्ण

		w2(0);
		WR(7,0);
		bpck_disconnect(pi);

		अवरोध;

	पूर्ण

	अगर (verbose) अणु
	    prपूर्णांकk("%s: bpck: 0x%x unit %d mode %d: ",
		   pi->device,pi->port,pi->unit,pi->mode);
	    क्रम (i=0;i<TEST_LEN;i++) prपूर्णांकk("%3d",buf[i]);
	    prपूर्णांकk("\n");
	पूर्ण

	e = 0;
	क्रम (i=0;i<TEST_LEN;i++) अगर (buf[i] != (i+1)) e++;
	वापस e;
पूर्ण

अटल व्योम bpck_पढ़ो_eeprom ( PIA *pi, अक्षर * buf )

अणु       पूर्णांक i, j, k, p, v, f, om, od;

	bpck_क्रमce_spp(pi);

	om = pi->mode;  od = pi->delay;
	pi->mode = 0; pi->delay = 6;

	bpck_connect(pi);
	
	WR(4,0);
	क्रम (i=0;i<64;i++) अणु
	    WR(6,8);  
	    WR(6,0xc);
	    p = 0x100;
	    क्रम (k=0;k<9;k++) अणु
		f = (((i + 0x180) & p) != 0) * 2;
		WR(6,f+0xc); 
		WR(6,f+0xd); 
		WR(6,f+0xc);
		p = (p >> 1);
	    पूर्ण
	    क्रम (j=0;j<2;j++) अणु
		v = 0;
		क्रम (k=0;k<8;k++) अणु
		    WR(6,0xc); 
		    WR(6,0xd); 
		    WR(6,0xc); 
		    f = RR(0);
		    v = 2*v + (f == 0x84);
		पूर्ण
		buf[2*i+1-j] = v;
	    पूर्ण
	पूर्ण
	WR(6,8);
	WR(6,0);
	WR(5,8);

	bpck_disconnect(pi);

        अगर (om >= 2) अणु
                bpck_connect(pi);
                WR(7,3);
                WR(4,8);
                bpck_disconnect(pi);
        पूर्ण

	pi->mode = om; pi->delay = od;
पूर्ण

अटल पूर्णांक bpck_test_port ( PIA *pi ) 	/* check क्रम 8-bit port */

अणु	पूर्णांक	i, r, m;

	w2(0x2c); i = r0(); w0(255-i); r = r0(); w0(i);
	m = -1;
	अगर (r == i) m = 2;
	अगर (r == (255-i)) m = 0;

	w2(0xc); i = r0(); w0(255-i); r = r0(); w0(i);
	अगर (r != (255-i)) m = -1;
	
	अगर (m == 0) अणु w2(6); w2(0xc); r = r0(); w0(0xaa); w0(r); w0(0xaa); पूर्ण
	अगर (m == 2) अणु w2(0x26); w2(0xc); पूर्ण

	अगर (m == -1) वापस 0;
	वापस 5;
पूर्ण

अटल व्योम bpck_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु	अक्षर	*mode_string[5] = अणु "4-bit","8-bit","EPP-8",
				    "EPP-16","EPP-32" पूर्ण;

#अगर_घोषित DUMP_EEPROM
	पूर्णांक i;
#पूर्ण_अगर

	bpck_पढ़ो_eeprom(pi,scratch);

#अगर_घोषित DUMP_EEPROM
	अगर (verbose) अणु
	   क्रम(i=0;i<128;i++)
		अगर ((scratch[i] < ' ') || (scratch[i] > '~'))
		    scratch[i] = '.';
	   prपूर्णांकk("%s: bpck EEPROM: %64.64s\n",pi->device,scratch);
	   prपूर्णांकk("%s:              %64.64s\n",pi->device,&scratch[64]);
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk("%s: bpck %s, backpack %8.8s unit %d",
		pi->device,BPCK_VERSION,&scratch[110],pi->unit);
	prपूर्णांकk(" at 0x%x, mode %d (%s), delay %d\n",pi->port,
		pi->mode,mode_string[pi->mode],pi->delay);
पूर्ण

अटल काष्ठा pi_protocol bpck = अणु
	.owner		= THIS_MODULE,
	.name		= "bpck",
	.max_mode	= 5,
	.epp_first	= 2,
	.शेष_delay	= 4,
	.max_units	= 255,
	.ग_लिखो_regr	= bpck_ग_लिखो_regr,
	.पढ़ो_regr	= bpck_पढ़ो_regr,
	.ग_लिखो_block	= bpck_ग_लिखो_block,
	.पढ़ो_block	= bpck_पढ़ो_block,
	.connect	= bpck_connect,
	.disconnect	= bpck_disconnect,
	.test_port	= bpck_test_port,
	.probe_unit	= bpck_probe_unit,
	.test_proto	= bpck_test_proto,
	.log_adapter	= bpck_log_adapter,
पूर्ण;

अटल पूर्णांक __init bpck_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&bpck);
पूर्ण

अटल व्योम __निकास bpck_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&bpck);
पूर्ण

MODULE_LICENSE("GPL");
module_init(bpck_init)
module_निकास(bpck_निकास)
