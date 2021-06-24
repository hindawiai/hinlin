<शैली गुरु>
/* 
	friq.c	(c) 1998    Grant R. Guenther <grant@torque.net>
		            Under the terms of the GNU General Public License

	friq.c is a low-level protocol driver क्रम the Freecom "IQ"
	parallel port IDE adapter.   Early versions of this adapter
	use the 'frpw' protocol.
	
	Freecom uses this adapter in a battery घातered बाह्यal 
	CD-ROM drive.  It is also used in LS-120 drives by
	Maxell and Panasonic, and other devices.

	The battery घातered drive requires software support to
	control the घातer to the drive.  This module enables the
	drive घातer when the high level driver (pcd) is loaded
	and disables it when the module is unloaded.  Note, अगर
	the friq module is built in to the kernel, the घातer
	will never be चयनed off, so other means should be
	used to conserve battery घातer.

*/

/* Changes:

	1.01	GRG 1998.12.20	 Added support क्रम soft घातer चयन
*/

#घोषणा	FRIQ_VERSION	"1.01" 

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा CMD(x)		w2(4);w0(0xff);w0(0xff);w0(0x73);w0(0x73);\
			w0(0xc9);w0(0xc9);w0(0x26);w0(0x26);w0(x);w0(x);

#घोषणा j44(l,h)	(((l>>4)&0x0f)|(h&0xf0))

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x08, 0x10 पूर्ण;

अटल पूर्णांक friq_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक	h,l,r;

	r = regr + cont_map[cont];

	CMD(r);
	w2(6); l = r1();
	w2(4); h = r1();
	w2(4); 

	वापस j44(l,h);

पूर्ण

अटल व्योम friq_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	पूर्णांक r;

        r = regr + cont_map[cont];

	CMD(r);
	w0(val);
	w2(5);w2(7);w2(5);w2(4);
पूर्ण

अटल व्योम friq_पढ़ो_block_पूर्णांक( PIA *pi, अक्षर * buf, पूर्णांक count, पूर्णांक regr )

अणु       पूर्णांक     h, l, k, ph;

        चयन(pi->mode) अणु

        हाल 0: CMD(regr); 
                क्रम (k=0;k<count;k++) अणु
                        w2(6); l = r1();
                        w2(4); h = r1();
                        buf[k] = j44(l,h);
                पूर्ण
                w2(4);
                अवरोध;

        हाल 1: ph = 2;
                CMD(regr+0xc0); 
                w0(0xff);
                क्रम (k=0;k<count;k++) अणु
                        w2(0xa4 + ph); 
                        buf[k] = r0();
                        ph = 2 - ph;
                पूर्ण 
                w2(0xac); w2(0xa4); w2(4);
                अवरोध;

	हाल 2: CMD(regr+0x80);
		क्रम (k=0;k<count-2;k++) buf[k] = r4();
		w2(0xac); w2(0xa4);
		buf[count-2] = r4();
		buf[count-1] = r4();
		w2(4);
		अवरोध;

	हाल 3: CMD(regr+0x80);
                क्रम (k=0;k<(count/2)-1;k++) ((u16 *)buf)[k] = r4w();
                w2(0xac); w2(0xa4);
                buf[count-2] = r4();
                buf[count-1] = r4();
                w2(4);
                अवरोध;

	हाल 4: CMD(regr+0x80);
                क्रम (k=0;k<(count/4)-1;k++) ((u32 *)buf)[k] = r4l();
                buf[count-4] = r4();
                buf[count-3] = r4();
                w2(0xac); w2(0xa4);
                buf[count-2] = r4();
                buf[count-1] = r4();
                w2(4);
                अवरोध;

        पूर्ण
पूर्ण

अटल व्योम friq_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count)

अणु	friq_पढ़ो_block_पूर्णांक(pi,buf,count,0x08);
पूर्ण

अटल व्योम friq_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )
 
अणु	पूर्णांक	k;

	चयन(pi->mode) अणु

	हाल 0:
	हाल 1: CMD(8); w2(5);
        	क्रम (k=0;k<count;k++) अणु
			w0(buf[k]);
			w2(7);w2(5);
		पूर्ण
		w2(4);
		अवरोध;

	हाल 2: CMD(0xc8); w2(5);
		क्रम (k=0;k<count;k++) w4(buf[k]);
		w2(4);
		अवरोध;

        हाल 3: CMD(0xc8); w2(5);
                क्रम (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(4);
                अवरोध;

        हाल 4: CMD(0xc8); w2(5);
                क्रम (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(4);
                अवरोध;
	पूर्ण
पूर्ण

अटल व्योम friq_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(4);
पूर्ण

अटल व्योम friq_disconnect ( PIA *pi )

अणु       CMD(0x20);
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल पूर्णांक friq_test_proto( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       पूर्णांक     j, k, r;
	पूर्णांक	e[2] = अणु0,0पूर्ण;

	pi->saved_r0 = r0();	
	w0(0xff); udelay(20); CMD(0x3d); /* turn the घातer on */
	udelay(500);
	w0(pi->saved_r0);

	friq_connect(pi);
	क्रम (j=0;j<2;j++) अणु
                friq_ग_लिखो_regr(pi,0,6,0xa0+j*0x10);
                क्रम (k=0;k<256;k++) अणु
                        friq_ग_लिखो_regr(pi,0,2,k^0xaa);
                        friq_ग_लिखो_regr(pi,0,3,k^0x55);
                        अगर (friq_पढ़ो_regr(pi,0,2) != (k^0xaa)) e[j]++;
                        पूर्ण
                पूर्ण
	friq_disconnect(pi);

	friq_connect(pi);
        friq_पढ़ो_block_पूर्णांक(pi,scratch,512,0x10);
        r = 0;
        क्रम (k=0;k<128;k++) अगर (scratch[k] != k) r++;
	friq_disconnect(pi);

        अगर (verbose)  अणु
            prपूर्णांकk("%s: friq: port 0x%x, mode %d, test=(%d,%d,%d)\n",
                   pi->device,pi->port,pi->mode,e[0],e[1],r);
        पूर्ण

        वापस (r || (e[0] && e[1]));
पूर्ण


अटल व्योम friq_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[6] = अणु"4-bit","8-bit",
				   "EPP-8","EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: friq %s, Freecom IQ ASIC-2 adapter at 0x%x, ", pi->device,
		FRIQ_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

	pi->निजी = 1;
	friq_connect(pi);
	CMD(0x9e);  		/* disable sleep समयr */
	friq_disconnect(pi);

पूर्ण

अटल व्योम friq_release_proto( PIA *pi)
अणु
	अगर (pi->निजी) अणु		/* turn off the घातer */
		friq_connect(pi);
		CMD(0x1d); CMD(0x1e);
		friq_disconnect(pi);
		pi->निजी = 0;
	पूर्ण
पूर्ण

अटल काष्ठा pi_protocol friq = अणु
	.owner		= THIS_MODULE,
	.name		= "friq",
	.max_mode	= 5,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= friq_ग_लिखो_regr,
	.पढ़ो_regr	= friq_पढ़ो_regr,
	.ग_लिखो_block	= friq_ग_लिखो_block,
	.पढ़ो_block	= friq_पढ़ो_block,
	.connect	= friq_connect,
	.disconnect	= friq_disconnect,
	.test_proto	= friq_test_proto,
	.log_adapter	= friq_log_adapter,
	.release_proto	= friq_release_proto,
पूर्ण;

अटल पूर्णांक __init friq_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&friq);
पूर्ण

अटल व्योम __निकास friq_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&friq);
पूर्ण

MODULE_LICENSE("GPL");
module_init(friq_init)
module_निकास(friq_निकास)
