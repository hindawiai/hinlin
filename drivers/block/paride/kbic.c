<शैली गुरु>
/*
        kbic.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

        This is a low-level driver क्रम the KBIC-951A and KBIC-971A
        parallel to IDE adapter chips from KingByte Inक्रमmation Systems.

	The chips are almost identical, however, the wakeup code 
	required क्रम the 971A पूर्णांकerferes with the correct operation of
        the 951A, so this driver रेजिस्टरs itself twice, once क्रम
	each chip.

*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto

*/

#घोषणा KBIC_VERSION      "1.01"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा r12w()			(delay_p,inw(pi->port+1)&0xffff) 

#घोषणा j44(a,b)                ((((a>>4)&0x0f)|(b&0xf0))^0x88)
#घोषणा j53(w)                  (((w>>3)&0x1f)|((w>>4)&0xe0))


/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x80, 0x40 पूर्ण;

अटल पूर्णांक kbic_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक     a, b, s;

        s = cont_map[cont];

	चयन (pi->mode) अणु

	हाल 0: w0(regr|0x18|s); w2(4); w2(6); w2(4); w2(1); w0(8);
	        a = r1(); w0(0x28); b = r1(); w2(4);
		वापस j44(a,b);

	हाल 1: w0(regr|0x38|s); w2(4); w2(6); w2(4); w2(5); w0(8);
		a = r12w(); w2(4);
		वापस j53(a);

	हाल 2: w0(regr|0x08|s); w2(4); w2(6); w2(4); w2(0xa5); w2(0xa1);
		a = r0(); w2(4);
       		वापस a;

	हाल 3:
	हाल 4:
	हाल 5: w0(0x20|s); w2(4); w2(6); w2(4); w3(regr);
		a = r4(); b = r4(); w2(4); w2(0); w2(4);
		वापस a;

	पूर्ण
	वापस -1;
पूर्ण       

अटल व्योम  kbic_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु       पूर्णांक  s;

        s = cont_map[cont];

        चयन (pi->mode) अणु

	हाल 0: 
        हाल 1:
	हाल 2:	w0(regr|0x10|s); w2(4); w2(6); w2(4); 
		w0(val); w2(5); w2(4);
		अवरोध;

	हाल 3:
	हाल 4:
	हाल 5: w0(0x20|s); w2(4); w2(6); w2(4); w3(regr);
		w4(val); w4(val);
		w2(4); w2(0); w2(4);
                अवरोध;

	पूर्ण
पूर्ण

अटल व्योम k951_connect ( PIA *pi  )

अणु 	pi->saved_r0 = r0();
        pi->saved_r2 = r2();
        w2(4); 
पूर्ण

अटल व्योम k951_disconnect ( PIA *pi )

अणु      	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण

#घोषणा	CCP(x)	w2(0xc4);w0(0xaa);w0(0x55);w0(0);w0(0xff);w0(0x87);\
		w0(0x78);w0(x);w2(0xc5);w2(0xc4);w0(0xff);

अटल व्योम k971_connect ( PIA *pi  )

अणु 	pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	CCP(0x20);
        w2(4); 
पूर्ण

अटल व्योम k971_disconnect ( PIA *pi )

अणु       CCP(0x30);
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण

/* counts must be congruent to 0 MOD 4, but all known applications
   have this property.
*/

अटल व्योम kbic_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     k, a, b;

        चयन (pi->mode) अणु

        हाल 0: w0(0x98); w2(4); w2(6); w2(4);
                क्रम (k=0;k<count/2;k++) अणु
			w2(1); w0(8);    a = r1();
			       w0(0x28); b = r1();
			buf[2*k]   = j44(a,b);
			w2(5);           b = r1();
			       w0(8);    a = r1();
			buf[2*k+1] = j44(a,b);
			w2(4);
                पूर्ण 
                अवरोध;

        हाल 1: w0(0xb8); w2(4); w2(6); w2(4); 
                क्रम (k=0;k<count/4;k++) अणु
                        w0(0xb8); 
			w2(4); w2(5); 
                        w0(8);    buf[4*k]   = j53(r12w());
			w0(0xb8); buf[4*k+1] = j53(r12w());
			w2(4); w2(5);
			          buf[4*k+3] = j53(r12w());
			w0(8);    buf[4*k+2] = j53(r12w());
                पूर्ण
                w2(4);
                अवरोध;

        हाल 2: w0(0x88); w2(4); w2(6); w2(4);
                क्रम (k=0;k<count/2;k++) अणु
                        w2(0xa0); w2(0xa1); buf[2*k] = r0();
                        w2(0xa5); buf[2*k+1] = r0();
                पूर्ण
                w2(4);
                अवरोध;

        हाल 3: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
                क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(4); w2(0); w2(4);
                अवरोध;

	हाल 4: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
                क्रम (k=0;k<count/2;k++) ((u16 *)buf)[k] = r4w();
                w2(4); w2(0); w2(4);
                अवरोध;

        हाल 5: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
                क्रम (k=0;k<count/4;k++) ((u32 *)buf)[k] = r4l();
                w2(4); w2(0); w2(4);
                अवरोध;


        पूर्ण
पूर्ण

अटल व्योम kbic_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     k;

        चयन (pi->mode) अणु

        हाल 0:
        हाल 1:
        हाल 2: w0(0x90); w2(4); w2(6); w2(4); 
		क्रम(k=0;k<count/2;k++) अणु
			w0(buf[2*k+1]); w2(0); w2(4); 
			w0(buf[2*k]);   w2(5); w2(4); 
		पूर्ण
		अवरोध;

        हाल 3: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		क्रम(k=0;k<count/2;k++) अणु
			w4(buf[2*k+1]); 
                        w4(buf[2*k]);
                पूर्ण
		w2(4); w2(0); w2(4);
		अवरोध;

	हाल 4: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
                क्रम(k=0;k<count/2;k++) w4w(pi_swab16(buf,k));
                w2(4); w2(0); w2(4);
                अवरोध;

        हाल 5: w0(0xa0); w2(4); w2(6); w2(4); w3(0);
                क्रम(k=0;k<count/4;k++) w4l(pi_swab32(buf,k));
                w2(4); w2(0); w2(4);
                अवरोध;

        पूर्ण

पूर्ण

अटल व्योम kbic_log_adapter( PIA *pi, अक्षर * scratch, 
			      पूर्णांक verbose, अक्षर * chip )

अणु       अक्षर    *mode_string[6] = अणु"4-bit","5/3","8-bit",
				   "EPP-8","EPP_16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: kbic %s, KingByte %s at 0x%x, ",
                pi->device,KBIC_VERSION,chip,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल व्योम k951_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु	kbic_log_adapter(pi,scratch,verbose,"KBIC-951A");
पूर्ण

अटल व्योम k971_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       kbic_log_adapter(pi,scratch,verbose,"KBIC-971A");
पूर्ण

अटल काष्ठा pi_protocol k951 = अणु
	.owner		= THIS_MODULE,
	.name		= "k951",
	.max_mode	= 6,
	.epp_first	= 3,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= kbic_ग_लिखो_regr,
	.पढ़ो_regr	= kbic_पढ़ो_regr,
	.ग_लिखो_block	= kbic_ग_लिखो_block,
	.पढ़ो_block	= kbic_पढ़ो_block,
	.connect	= k951_connect,
	.disconnect	= k951_disconnect,
	.log_adapter	= k951_log_adapter,
पूर्ण;

अटल काष्ठा pi_protocol k971 = अणु
	.owner		= THIS_MODULE,
	.name		= "k971",
	.max_mode	= 6,
	.epp_first	= 3,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= kbic_ग_लिखो_regr,
	.पढ़ो_regr	= kbic_पढ़ो_regr,
	.ग_लिखो_block	= kbic_ग_लिखो_block,
	.पढ़ो_block	= kbic_पढ़ो_block,
	.connect	= k971_connect,
	.disconnect	= k971_disconnect,
	.log_adapter	= k971_log_adapter,
पूर्ण;

अटल पूर्णांक __init kbic_init(व्योम)
अणु
	पूर्णांक rv;

	rv = paride_रेजिस्टर(&k951);
	अगर (rv < 0)
		वापस rv;
	rv = paride_रेजिस्टर(&k971);
	अगर (rv < 0)
		paride_unरेजिस्टर(&k951);
	वापस rv;
पूर्ण

अटल व्योम __निकास kbic_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&k951);
	paride_unरेजिस्टर(&k971);
पूर्ण

MODULE_LICENSE("GPL");
module_init(kbic_init)
module_निकास(kbic_निकास)
