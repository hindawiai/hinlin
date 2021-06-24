<शैली गुरु>
/* 
	on20.c	(c) 1996-8  Grant R. Guenther <grant@torque.net>
		            Under the terms of the GNU General Public License.

        on20.c is a low-level protocol driver क्रम the
        Onspec 90c20 parallel to IDE adapter. 
*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto

*/

#घोषणा	ON20_VERSION	"1.01"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा op(f)	w2(4);w0(f);w2(5);w2(0xd);w2(5);w2(0xd);w2(5);w2(4);
#घोषणा vl(v)	w2(4);w0(v);w2(5);w2(7);w2(5);w2(4);

#घोषणा j44(a,b)  (((a>>4)&0x0f)|(b&0xf0))

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक on20_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक h,l, r ;

        r = (regr<<2) + 1 + cont;

        op(1); vl(r); op(0);

	चयन (pi->mode)  अणु

        हाल 0:  w2(4); w2(6); l = r1();
                 w2(4); w2(6); h = r1();
                 w2(4); w2(6); w2(4); w2(6); w2(4);
		 वापस j44(l,h);

	हाल 1:  w2(4); w2(0x26); r = r0(); 
                 w2(4); w2(0x26); w2(4);
		 वापस r;

	पूर्ण
	वापस -1;
पूर्ण	

अटल व्योम on20_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val )

अणु	पूर्णांक r;

	r = (regr<<2) + 1 + cont;

	op(1); vl(r); 
	op(0); vl(val); 
	op(0); vl(val);
पूर्ण

अटल व्योम on20_connect ( PIA *pi)

अणु	pi->saved_r0 = r0();
        pi->saved_r2 = r2();

	w2(4);w0(0);w2(0xc);w2(4);w2(6);w2(4);w2(6);w2(4); 
	अगर (pi->mode) अणु op(2); vl(8); op(2); vl(9); पूर्ण
	       अन्यथा   अणु op(2); vl(0); op(2); vl(8); पूर्ण
पूर्ण

अटल व्योम on20_disconnect ( PIA *pi )

अणु	w2(4);w0(7);w2(4);w2(0xc);w2(4);
        w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम on20_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक     k, l, h; 

	op(1); vl(1); op(0);

	क्रम (k=0;k<count;k++) 
	    अगर (pi->mode) अणु
		w2(4); w2(0x26); buf[k] = r0();
	    पूर्ण अन्यथा अणु
		w2(6); l = r1(); w2(4);
		w2(6); h = r1(); w2(4);
		buf[k] = j44(l,h);
	    पूर्ण
	w2(4);
पूर्ण

अटल व्योम on20_ग_लिखो_block(  PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक	k;

	op(1); vl(1); op(0);

	क्रम (k=0;k<count;k++) अणु w2(5); w0(buf[k]); w2(7); पूर्ण
	w2(4);
पूर्ण

अटल व्योम on20_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[2] = अणु"4-bit","8-bit"पूर्ण;

        prपूर्णांकk("%s: on20 %s, OnSpec 90c20 at 0x%x, ",
                pi->device,ON20_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol on20 = अणु
	.owner		= THIS_MODULE,
	.name		= "on20",
	.max_mode	= 2,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= on20_ग_लिखो_regr,
	.पढ़ो_regr	= on20_पढ़ो_regr,
	.ग_लिखो_block	= on20_ग_लिखो_block,
	.पढ़ो_block	= on20_पढ़ो_block,
	.connect	= on20_connect,
	.disconnect	= on20_disconnect,
	.log_adapter	= on20_log_adapter,
पूर्ण;

अटल पूर्णांक __init on20_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&on20);
पूर्ण

अटल व्योम __निकास on20_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&on20);
पूर्ण

MODULE_LICENSE("GPL");
module_init(on20_init)
module_निकास(on20_निकास)
