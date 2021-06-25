<शैली गुरु>
/* 
        aten.c  (c) 1997-8  Grant R. Guenther <grant@torque.net>
                            Under the terms of the GNU General Public License.

	aten.c is a low-level protocol driver क्रम the ATEN EH-100
	parallel port adapter.  The EH-100 supports 4-bit and 8-bit
        modes only.  There is also an EH-132 which supports EPP mode
        transfers.  The EH-132 is not yet supported.

*/

/* Changes:

	1.01	GRG 1998.05.05	init_proto, release_proto

*/

#घोषणा ATEN_VERSION      "1.01"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा j44(a,b)                ((((a>>4)&0x0f)|(b&0xf0))^0x88)

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x08, 0x20 पूर्ण;

अटल व्योम  aten_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	पूर्णांक r;

	r = regr + cont_map[cont] + 0x80;

	w0(r); w2(0xe); w2(6); w0(val); w2(7); w2(6); w2(0xc);
पूर्ण

अटल पूर्णांक aten_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक  a, b, r;

        r = regr + cont_map[cont] + 0x40;

	चयन (pi->mode) अणु

        हाल 0: w0(r); w2(0xe); w2(6); 
		w2(7); w2(6); w2(0);
		a = r1(); w0(0x10); b = r1(); w2(0xc);
		वापस j44(a,b);

        हाल 1: r |= 0x10;
		w0(r); w2(0xe); w2(6); w0(0xff); 
		w2(0x27); w2(0x26); w2(0x20);
		a = r0();
		w2(0x26); w2(0xc);
		वापस a;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम aten_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक  k, a, b, c, d;

	चयन (pi->mode) अणु

	हाल 0:	w0(0x48); w2(0xe); w2(6);
		क्रम (k=0;k<count/2;k++) अणु
			w2(7); w2(6); w2(2);
			a = r1(); w0(0x58); b = r1();
			w2(0); d = r1(); w0(0x48); c = r1();
			buf[2*k] = j44(c,d);
			buf[2*k+1] = j44(a,b);
		पूर्ण
		w2(0xc);
		अवरोध;

	हाल 1: w0(0x58); w2(0xe); w2(6);
		क्रम (k=0;k<count/2;k++) अणु
			w2(0x27); w2(0x26); w2(0x22);
			a = r0(); w2(0x20); b = r0();
			buf[2*k] = b; buf[2*k+1] = a;
		पूर्ण
		w2(0x26); w2(0xc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aten_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु	पूर्णांक k;

	w0(0x88); w2(0xe); w2(6);
	क्रम (k=0;k<count/2;k++) अणु
		w0(buf[2*k+1]); w2(0xe); w2(6);
		w0(buf[2*k]); w2(7); w2(6);
	पूर्ण
	w2(0xc);
पूर्ण

अटल व्योम aten_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xc);	
पूर्ण

अटल व्योम aten_disconnect ( PIA *pi )

अणु       w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम aten_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[2] = अणु"4-bit","8-bit"पूर्ण;

        prपूर्णांकk("%s: aten %s, ATEN EH-100 at 0x%x, ",
                pi->device,ATEN_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol aten = अणु
	.owner		= THIS_MODULE,
	.name		= "aten",
	.max_mode	= 2,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= aten_ग_लिखो_regr,
	.पढ़ो_regr	= aten_पढ़ो_regr,
	.ग_लिखो_block	= aten_ग_लिखो_block,
	.पढ़ो_block	= aten_पढ़ो_block,
	.connect	= aten_connect,
	.disconnect	= aten_disconnect,
	.log_adapter	= aten_log_adapter,
पूर्ण;

अटल पूर्णांक __init aten_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&aten);
पूर्ण

अटल व्योम __निकास aten_निकास(व्योम)
अणु
	paride_unरेजिस्टर( &aten );
पूर्ण

MODULE_LICENSE("GPL");
module_init(aten_init)
module_निकास(aten_निकास)
