<शैली गुरु>
/* 
        dstr.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

        dstr.c is a low-level protocol driver क्रम the 
        DataStor EP2000 parallel to IDE adapter chip.

*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto

*/

#घोषणा DSTR_VERSION      "1.01"

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

#घोषणा j44(a,b)  (((a>>3)&0x07)|((~a>>4)&0x08)|((b<<1)&0x70)|((~b)&0x80))

#घोषणा P1	w2(5);w2(0xd);w2(5);w2(4);
#घोषणा P2	w2(5);w2(7);w2(5);w2(4);
#घोषणा P3      w2(6);w2(4);w2(6);w2(4);

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x20, 0x40 पूर्ण;

अटल पूर्णांक dstr_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक     a, b, r;

        r = regr + cont_map[cont];

	w0(0x81); P1;
	अगर (pi->mode) अणु w0(0x11); पूर्ण अन्यथा अणु w0(1); पूर्ण
	P2; w0(r); P1;

        चयन (pi->mode)  अणु

        हाल 0: w2(6); a = r1(); w2(4); w2(6); b = r1(); w2(4);
                वापस j44(a,b);

        हाल 1: w0(0); w2(0x26); a = r0(); w2(4);
                वापस a;

	हाल 2:
	हाल 3:
        हाल 4: w2(0x24); a = r4(); w2(4);
                वापस a;

        पूर्ण
        वापस -1;
पूर्ण       

अटल व्योम dstr_ग_लिखो_regr(  PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val )

अणु       पूर्णांक  r;

        r = regr + cont_map[cont];

	w0(0x81); P1; 
	अगर (pi->mode >= 2) अणु w0(0x11); पूर्ण अन्यथा अणु w0(1); पूर्ण
	P2; w0(r); P1;
	
        चयन (pi->mode)  अणु

        हाल 0:
        हाल 1: w0(val); w2(5); w2(7); w2(5); w2(4);
		अवरोध;

	हाल 2:
	हाल 3:
        हाल 4: w4(val); 
                अवरोध;
        पूर्ण
पूर्ण

#घोषणा  CCP(x)  w0(0xff);w2(0xc);w2(4);\
		 w0(0xaa);w0(0x55);w0(0);w0(0xff);w0(0x87);w0(0x78);\
		 w0(x);w2(5);w2(4);

अटल व्योम dstr_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
        w2(4); CCP(0xe0); w0(0xff);
पूर्ण

अटल व्योम dstr_disconnect ( PIA *pi )

अणु       CCP(0x30);
        w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम dstr_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     k, a, b;

        w0(0x81); P1;
        अगर (pi->mode) अणु w0(0x19); पूर्ण अन्यथा अणु w0(9); पूर्ण
	P2; w0(0x82); P1; P3; w0(0x20); P1;

        चयन (pi->mode) अणु

        हाल 0: क्रम (k=0;k<count;k++) अणु
                        w2(6); a = r1(); w2(4);
                        w2(6); b = r1(); w2(4);
                        buf[k] = j44(a,b);
                पूर्ण 
                अवरोध;

        हाल 1: w0(0);
                क्रम (k=0;k<count;k++) अणु
                        w2(0x26); buf[k] = r0(); w2(0x24);
                पूर्ण
                w2(4);
                अवरोध;

        हाल 2: w2(0x24); 
                क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(4);
                अवरोध;

        हाल 3: w2(0x24); 
                क्रम (k=0;k<count/2;k++) ((u16 *)buf)[k] = r4w();
                w2(4);
                अवरोध;

        हाल 4: w2(0x24); 
                क्रम (k=0;k<count/4;k++) ((u32 *)buf)[k] = r4l();
                w2(4);
                अवरोध;

        पूर्ण
पूर्ण

अटल व्योम dstr_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक	k;

        w0(0x81); P1;
        अगर (pi->mode) अणु w0(0x19); पूर्ण अन्यथा अणु w0(9); पूर्ण
        P2; w0(0x82); P1; P3; w0(0x20); P1;

        चयन (pi->mode) अणु

        हाल 0:
        हाल 1: क्रम (k=0;k<count;k++) अणु
                        w2(5); w0(buf[k]); w2(7);
                पूर्ण
                w2(5); w2(4);
                अवरोध;

        हाल 2: w2(0xc5);
                क्रम (k=0;k<count;k++) w4(buf[k]);
		w2(0xc4);
                अवरोध;

        हाल 3: w2(0xc5);
                क्रम (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(0xc4);
                अवरोध;

        हाल 4: w2(0xc5);
                क्रम (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(0xc4);
                अवरोध;

        पूर्ण
पूर्ण


अटल व्योम dstr_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[5] = अणु"4-bit","8-bit","EPP-8",
				   "EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: dstr %s, DataStor EP2000 at 0x%x, ",
                pi->device,DSTR_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol dstr = अणु
	.owner		= THIS_MODULE,
	.name		= "dstr",
	.max_mode	= 5,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= dstr_ग_लिखो_regr,
	.पढ़ो_regr	= dstr_पढ़ो_regr,
	.ग_लिखो_block	= dstr_ग_लिखो_block,
	.पढ़ो_block	= dstr_पढ़ो_block,
	.connect	= dstr_connect,
	.disconnect	= dstr_disconnect,
	.log_adapter	= dstr_log_adapter,
पूर्ण;

अटल पूर्णांक __init dstr_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&dstr);
पूर्ण

अटल व्योम __निकास dstr_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&dstr);
पूर्ण

MODULE_LICENSE("GPL");
module_init(dstr_init)
module_निकास(dstr_निकास)
