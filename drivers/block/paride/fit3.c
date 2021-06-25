<शैली गुरु>
/* 
        fit3.c        (c) 1998  Grant R. Guenther <grant@torque.net>
                          Under the terms of the GNU General Public License.

	fit3.c is a low-level protocol driver क्रम newer models 
        of the Fidelity International Technology parallel port adapter.  
	This adapter is used in their TransDisk 3000 portable 
	hard-drives, as well as CD-ROM, PD-CD and other devices.

	The TD-2000 and certain older devices use a dअगरferent protocol.
	Try the fit2 protocol module with them.

        NB:  The FIT adapters करो not appear to support the control 
	रेजिस्टरs.  So, we map ALT_STATUS to STATUS and NO-OP ग_लिखोs 
	to the device control रेजिस्टर - this means that IDE reset 
	will not work on these devices.

*/

#घोषणा FIT3_VERSION      "1.0"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा j44(a,b)                (((a>>3)&0x0f)|((b<<1)&0xf0))

#घोषणा w7(byte)                अणुout_p(7,byte);पूर्ण
#घोषणा r7()                    (in_p(7) & 0xff)

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 

*/

अटल व्योम  fit3_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	अगर (cont == 1) वापस;

	चयन (pi->mode) अणु

	हाल 0:
	हाल 1: w2(0xc); w0(regr); w2(0x8); w2(0xc); 
		w0(val); w2(0xd); 
		w0(0);   w2(0xc);
		अवरोध;

	हाल 2: w2(0xc); w0(regr); w2(0x8); w2(0xc);
		w4(val); w4(0);
		w2(0xc);
		अवरोध;

	पूर्ण
पूर्ण

अटल पूर्णांक fit3_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक  a, b;

	अगर (cont) अणु
	  अगर (regr != 6) वापस 0xff;
	  regr = 7;
	पूर्ण 

	चयन (pi->mode) अणु

	हाल 0: w2(0xc); w0(regr + 0x10); w2(0x8); w2(0xc);
		w2(0xd); a = r1();
		w2(0xf); b = r1(); 
		w2(0xc);
		वापस j44(a,b);

	हाल 1: w2(0xc); w0(regr + 0x90); w2(0x8); w2(0xc);
		w2(0xec); w2(0xee); w2(0xef); a = r0(); 
		w2(0xc);
		वापस a;

	हाल 2: w2(0xc); w0(regr + 0x90); w2(0x8); w2(0xc); 
		w2(0xec); 
		a = r4(); b = r4(); 
		w2(0xc);
		वापस a;

	पूर्ण
	वापस -1; 

पूर्ण

अटल व्योम fit3_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक  k, a, b, c, d;

	चयन (pi->mode) अणु

	हाल 0: w2(0xc); w0(0x10); w2(0x8); w2(0xc);
		क्रम (k=0;k<count/2;k++) अणु
		    w2(0xd); a = r1();
		    w2(0xf); b = r1();
		    w2(0xc); c = r1();
		    w2(0xe); d = r1();
		    buf[2*k  ] = j44(a,b);
		    buf[2*k+1] = j44(c,d);
		पूर्ण
		w2(0xc);
		अवरोध;

	हाल 1: w2(0xc); w0(0x90); w2(0x8); w2(0xc); 
		w2(0xec); w2(0xee);
		क्रम (k=0;k<count/2;k++) अणु
		    w2(0xef); a = r0();
		    w2(0xee); b = r0();
                    buf[2*k  ] = a;
                    buf[2*k+1] = b;
		पूर्ण
		w2(0xec); 
		w2(0xc);
		अवरोध;

	हाल 2: w2(0xc); w0(0x90); w2(0x8); w2(0xc); 
                w2(0xec);
		क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(0xc);
		अवरोध;

	पूर्ण
पूर्ण

अटल व्योम fit3_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक k;

        चयन (pi->mode) अणु

	हाल 0:
        हाल 1: w2(0xc); w0(0); w2(0x8); w2(0xc);
                क्रम (k=0;k<count/2;k++) अणु
 		    w0(buf[2*k  ]); w2(0xd);
 		    w0(buf[2*k+1]); w2(0xc);
		पूर्ण
		अवरोध;

        हाल 2: w2(0xc); w0(0); w2(0x8); w2(0xc); 
                क्रम (k=0;k<count;k++) w4(buf[k]);
                w2(0xc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fit3_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xc); w0(0); w2(0xa);
	अगर (pi->mode == 2) अणु 
		w2(0xc); w0(0x9); w2(0x8); w2(0xc); 
		पूर्ण
पूर्ण

अटल व्योम fit3_disconnect ( PIA *pi )

अणु       w2(0xc); w0(0xa); w2(0x8); w2(0xc);
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम fit3_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[3] = अणु"4-bit","8-bit","EPP"पूर्ण;

	prपूर्णांकk("%s: fit3 %s, FIT 3000 adapter at 0x%x, "
	       "mode %d (%s), delay %d\n",
                pi->device,FIT3_VERSION,pi->port,
		pi->mode,mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol fit3 = अणु
	.owner		= THIS_MODULE,
	.name		= "fit3",
	.max_mode	= 3,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= fit3_ग_लिखो_regr,
	.पढ़ो_regr	= fit3_पढ़ो_regr,
	.ग_लिखो_block	= fit3_ग_लिखो_block,
	.पढ़ो_block	= fit3_पढ़ो_block,
	.connect	= fit3_connect,
	.disconnect	= fit3_disconnect,
	.log_adapter	= fit3_log_adapter,
पूर्ण;

अटल पूर्णांक __init fit3_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&fit3);
पूर्ण

अटल व्योम __निकास fit3_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&fit3);
पूर्ण

MODULE_LICENSE("GPL");
module_init(fit3_init)
module_निकास(fit3_निकास)
