<शैली गुरु>
/* 
        ktti.c        (c) 1998  Grant R. Guenther <grant@torque.net>
                          Under the terms of the GNU General Public License.

	ktti.c is a low-level protocol driver क्रम the KT Technology
	parallel port adapter.  This adapter is used in the "PHd" 
        portable hard-drives.  As far as I can tell, this device
	supports 4-bit mode _only_.  

*/

#घोषणा KTTI_VERSION      "1.0"

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
*/

अटल पूर्णांक  cont_map[2] = अणु 0x10, 0x08 पूर्ण;

अटल व्योम  ktti_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	पूर्णांक r;

	r = regr + cont_map[cont];

	w0(r); w2(0xb); w2(0xa); w2(3); w2(6); 
	w0(val); w2(3); w0(0); w2(6); w2(0xb);
पूर्ण

अटल पूर्णांक ktti_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक  a, b, r;

        r = regr + cont_map[cont];

        w0(r); w2(0xb); w2(0xa); w2(9); w2(0xc); w2(9); 
	a = r1(); w2(0xc);  b = r1(); w2(9); w2(0xc); w2(9);
	वापस j44(a,b);

पूर्ण

अटल व्योम ktti_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक  k, a, b;

	क्रम (k=0;k<count/2;k++) अणु
		w0(0x10); w2(0xb); w2(0xa); w2(9); w2(0xc); w2(9);
		a = r1(); w2(0xc); b = r1(); w2(9);
		buf[2*k] = j44(a,b);
		a = r1(); w2(0xc); b = r1(); w2(9);
		buf[2*k+1] = j44(a,b);
	पूर्ण
पूर्ण

अटल व्योम ktti_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक k;

	क्रम (k=0;k<count/2;k++) अणु
		w0(0x10); w2(0xb); w2(0xa); w2(3); w2(6);
		w0(buf[2*k]); w2(3);
		w0(buf[2*k+1]); w2(6);
		w2(0xb);
	पूर्ण
पूर्ण

अटल व्योम ktti_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xb); w2(0xa); w0(0); w2(3); w2(6);	
पूर्ण

अटल व्योम ktti_disconnect ( PIA *pi )

अणु       w2(0xb); w2(0xa); w0(0xa0); w2(3); w2(4);
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम ktti_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       prपूर्णांकk("%s: ktti %s, KT adapter at 0x%x, delay %d\n",
                pi->device,KTTI_VERSION,pi->port,pi->delay);

पूर्ण

अटल काष्ठा pi_protocol ktti = अणु
	.owner		= THIS_MODULE,
	.name		= "ktti",
	.max_mode	= 1,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= ktti_ग_लिखो_regr,
	.पढ़ो_regr	= ktti_पढ़ो_regr,
	.ग_लिखो_block	= ktti_ग_लिखो_block,
	.पढ़ो_block	= ktti_पढ़ो_block,
	.connect	= ktti_connect,
	.disconnect	= ktti_disconnect,
	.log_adapter	= ktti_log_adapter,
पूर्ण;

अटल पूर्णांक __init ktti_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&ktti);
पूर्ण

अटल व्योम __निकास ktti_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&ktti);
पूर्ण

MODULE_LICENSE("GPL");
module_init(ktti_init)
module_निकास(ktti_निकास)
