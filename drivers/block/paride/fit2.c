<शैली गुरु>
/* 
        fit2.c        (c) 1998  Grant R. Guenther <grant@torque.net>
                          Under the terms of the GNU General Public License.

	fit2.c is a low-level protocol driver क्रम the older version
        of the Fidelity International Technology parallel port adapter.  
	This adapter is used in their TransDisk 2000 and older TransDisk
	3000 portable hard-drives.  As far as I can tell, this device
	supports 4-bit mode _only_.  

	Newer models of the FIT products use an enhanced protocol.
	The "fit3" protocol module should support current drives.

*/

#घोषणा FIT2_VERSION      "1.0"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा j44(a,b)                (((a>>4)&0x0f)|(b&0xf0))

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 

NB:  The FIT adapter करोes not appear to use the control रेजिस्टरs.
So, we map ALT_STATUS to STATUS and NO-OP ग_लिखोs to the device
control रेजिस्टर - this means that IDE reset will not work on these
devices.

*/

अटल व्योम  fit2_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	अगर (cont == 1) वापस;
	w2(0xc); w0(regr); w2(4); w0(val); w2(5); w0(0); w2(4);
पूर्ण

अटल पूर्णांक fit2_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक  a, b, r;

	अगर (cont) अणु
	  अगर (regr != 6) वापस 0xff;
	  r = 7;
	पूर्ण अन्यथा r = regr + 0x10;

	w2(0xc); w0(r); w2(4); w2(5); 
	         w0(0); a = r1();
	         w0(1); b = r1();
	w2(4);

	वापस j44(a,b);

पूर्ण

अटल व्योम fit2_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक  k, a, b, c, d;

	w2(0xc); w0(0x10);

	क्रम (k=0;k<count/4;k++) अणु

		w2(4); w2(5);
		w0(0); a = r1(); w0(1); b = r1();
		w0(3); c = r1(); w0(2); d = r1(); 
		buf[4*k+0] = j44(a,b);
		buf[4*k+1] = j44(d,c);

                w2(4); w2(5);
                       a = r1(); w0(3); b = r1();
                w0(1); c = r1(); w0(0); d = r1(); 
                buf[4*k+2] = j44(d,c);
                buf[4*k+3] = j44(a,b);

	पूर्ण

	w2(4);

पूर्ण

अटल व्योम fit2_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक k;


	w2(0xc); w0(0); 
	क्रम (k=0;k<count/2;k++) अणु
		w2(4); w0(buf[2*k]); 
		w2(5); w0(buf[2*k+1]);
	पूर्ण
	w2(4);
पूर्ण

अटल व्योम fit2_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xcc); 
पूर्ण

अटल व्योम fit2_disconnect ( PIA *pi )

अणु       w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम fit2_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       prपूर्णांकk("%s: fit2 %s, FIT 2000 adapter at 0x%x, delay %d\n",
                pi->device,FIT2_VERSION,pi->port,pi->delay);

पूर्ण

अटल काष्ठा pi_protocol fit2 = अणु
	.owner		= THIS_MODULE,
	.name		= "fit2",
	.max_mode	= 1,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= fit2_ग_लिखो_regr,
	.पढ़ो_regr	= fit2_पढ़ो_regr,
	.ग_लिखो_block	= fit2_ग_लिखो_block,
	.पढ़ो_block	= fit2_पढ़ो_block,
	.connect	= fit2_connect,
	.disconnect	= fit2_disconnect,
	.log_adapter	= fit2_log_adapter,
पूर्ण;

अटल पूर्णांक __init fit2_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&fit2);
पूर्ण

अटल व्योम __निकास fit2_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&fit2);
पूर्ण

MODULE_LICENSE("GPL");
module_init(fit2_init)
module_निकास(fit2_निकास)
