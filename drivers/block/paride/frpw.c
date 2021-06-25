<शैली गुरु>
/* 
	frpw.c	(c) 1996-8  Grant R. Guenther <grant@torque.net>
		            Under the terms of the GNU General Public License

	frpw.c is a low-level protocol driver क्रम the Freecom "Power"
	parallel port IDE adapter.
	
	Some applications of this adapter may require a "printer" reset
	prior to loading the driver.  This can be करोne by loading and
	unloading the "lp" driver, or it can be करोne by this driver
	अगर you define FRPW_HARD_RESET.  The latter is not recommended
	as it may upset devices on other ports.

*/

/* Changes:

        1.01    GRG 1998.05.06 init_proto, release_proto
			       fix chip detect
			       added EPP-16 and EPP-32
	1.02    GRG 1998.09.23 added hard reset to initialisation process
	1.03    GRG 1998.12.14 made hard reset conditional

*/

#घोषणा	FRPW_VERSION	"1.03" 

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>

#समावेश "paride.h"

#घोषणा cec4		w2(0xc);w2(0xe);w2(0xe);w2(0xc);w2(4);w2(4);w2(4);
#घोषणा j44(l,h)	(((l>>4)&0x0f)|(h&0xf0))

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x08, 0x10 पूर्ण;

अटल पूर्णांक frpw_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु	पूर्णांक	h,l,r;

	r = regr + cont_map[cont];

	w2(4);
	w0(r); cec4;
	w2(6); l = r1();
	w2(4); h = r1();
	w2(4); 

	वापस j44(l,h);

पूर्ण

अटल व्योम frpw_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)

अणु	पूर्णांक r;

        r = regr + cont_map[cont];

	w2(4); w0(r); cec4; 
	w0(val);
	w2(5);w2(7);w2(5);w2(4);
पूर्ण

अटल व्योम frpw_पढ़ो_block_पूर्णांक( PIA *pi, अक्षर * buf, पूर्णांक count, पूर्णांक regr )

अणु       पूर्णांक     h, l, k, ph;

        चयन(pi->mode) अणु

        हाल 0: w2(4); w0(regr); cec4;
                क्रम (k=0;k<count;k++) अणु
                        w2(6); l = r1();
                        w2(4); h = r1();
                        buf[k] = j44(l,h);
                पूर्ण
                w2(4);
                अवरोध;

        हाल 1: ph = 2;
                w2(4); w0(regr + 0xc0); cec4;
                w0(0xff);
                क्रम (k=0;k<count;k++) अणु
                        w2(0xa4 + ph); 
                        buf[k] = r0();
                        ph = 2 - ph;
                पूर्ण 
                w2(0xac); w2(0xa4); w2(4);
                अवरोध;

        हाल 2: w2(4); w0(regr + 0x80); cec4;
                क्रम (k=0;k<count;k++) buf[k] = r4();
                w2(0xac); w2(0xa4);
                w2(4);
                अवरोध;

	हाल 3: w2(4); w0(regr + 0x80); cec4;
		क्रम (k=0;k<count-2;k++) buf[k] = r4();
		w2(0xac); w2(0xa4);
		buf[count-2] = r4();
		buf[count-1] = r4();
		w2(4);
		अवरोध;

	हाल 4: w2(4); w0(regr + 0x80); cec4;
                क्रम (k=0;k<(count/2)-1;k++) ((u16 *)buf)[k] = r4w();
                w2(0xac); w2(0xa4);
                buf[count-2] = r4();
                buf[count-1] = r4();
                w2(4);
                अवरोध;

	हाल 5: w2(4); w0(regr + 0x80); cec4;
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

अटल व्योम frpw_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count)

अणु	frpw_पढ़ो_block_पूर्णांक(pi,buf,count,0x08);
पूर्ण

अटल व्योम frpw_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )
 
अणु	पूर्णांक	k;

	चयन(pi->mode) अणु

	हाल 0:
	हाल 1:
	हाल 2: w2(4); w0(8); cec4; w2(5);
        	क्रम (k=0;k<count;k++) अणु
			w0(buf[k]);
			w2(7);w2(5);
		पूर्ण
		w2(4);
		अवरोध;

	हाल 3: w2(4); w0(0xc8); cec4; w2(5);
		क्रम (k=0;k<count;k++) w4(buf[k]);
		w2(4);
		अवरोध;

        हाल 4: w2(4); w0(0xc8); cec4; w2(5);
                क्रम (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(4);
                अवरोध;

        हाल 5: w2(4); w0(0xc8); cec4; w2(5);
                क्रम (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(4);
                अवरोध;
	पूर्ण
पूर्ण

अटल व्योम frpw_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(4);
पूर्ण

अटल व्योम frpw_disconnect ( PIA *pi )

अणु       w2(4); w0(0x20); cec4;
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

/* Stub logic to see अगर PNP string is available - used to distinguish
   between the Xilinx and ASIC implementations of the Freecom adapter.
*/

अटल पूर्णांक frpw_test_pnp ( PIA *pi )

/*  वापसs chip_type:   0 = Xilinx, 1 = ASIC   */

अणु	पूर्णांक olddelay, a, b;

#अगर_घोषित FRPW_HARD_RESET
        w0(0); w2(8); udelay(50); w2(0xc);   /* parallel bus reset */
        mdelay(1500);
#पूर्ण_अगर

	olddelay = pi->delay;
	pi->delay = 10;

	pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	
	w2(4); w0(4); w2(6); w2(7);
	a = r1() & 0xff; w2(4); b = r1() & 0xff;
	w2(0xc); w2(0xe); w2(4);

	pi->delay = olddelay;
        w0(pi->saved_r0);
        w2(pi->saved_r2);

	वापस ((~a&0x40) && (b&0x40));
पूर्ण 

/* We use the pi->निजी to remember the result of the PNP test.
   To make this work, निजी = port*2 + chip.  Yes, I know it's
   a hack :-(
*/

अटल पूर्णांक frpw_test_proto( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       पूर्णांक     j, k, r;
	पूर्णांक	e[2] = अणु0,0पूर्ण;

	अगर ((pi->निजी>>1) != pi->port)
	   pi->निजी = frpw_test_pnp(pi) + 2*pi->port;

	अगर (((pi->निजी%2) == 0) && (pi->mode > 2)) अणु
	   अगर (verbose) 
		prपूर्णांकk("%s: frpw: Xilinx does not support mode %d\n",
			pi->device, pi->mode);
	   वापस 1;
	पूर्ण

	अगर (((pi->निजी%2) == 1) && (pi->mode == 2)) अणु
	   अगर (verbose)
		prपूर्णांकk("%s: frpw: ASIC does not support mode 2\n",
			pi->device);
	   वापस 1;
	पूर्ण

	frpw_connect(pi);
	क्रम (j=0;j<2;j++) अणु
                frpw_ग_लिखो_regr(pi,0,6,0xa0+j*0x10);
                क्रम (k=0;k<256;k++) अणु
                        frpw_ग_लिखो_regr(pi,0,2,k^0xaa);
                        frpw_ग_लिखो_regr(pi,0,3,k^0x55);
                        अगर (frpw_पढ़ो_regr(pi,0,2) != (k^0xaa)) e[j]++;
                        पूर्ण
                पूर्ण
	frpw_disconnect(pi);

	frpw_connect(pi);
        frpw_पढ़ो_block_पूर्णांक(pi,scratch,512,0x10);
        r = 0;
        क्रम (k=0;k<128;k++) अगर (scratch[k] != k) r++;
	frpw_disconnect(pi);

        अगर (verbose)  अणु
            prपूर्णांकk("%s: frpw: port 0x%x, chip %ld, mode %d, test=(%d,%d,%d)\n",
                   pi->device,pi->port,(pi->निजी%2),pi->mode,e[0],e[1],r);
        पूर्ण

        वापस (r || (e[0] && e[1]));
पूर्ण


अटल व्योम frpw_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[6] = अणु"4-bit","8-bit","EPP",
				   "EPP-8","EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: frpw %s, Freecom (%s) adapter at 0x%x, ", pi->device,
		FRPW_VERSION,((pi->निजी%2) == 0)?"Xilinx":"ASIC",pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol frpw = अणु
	.owner		= THIS_MODULE,
	.name		= "frpw",
	.max_mode	= 6,
	.epp_first	= 2,
	.शेष_delay	= 2,
	.max_units	= 1,
	.ग_लिखो_regr	= frpw_ग_लिखो_regr,
	.पढ़ो_regr	= frpw_पढ़ो_regr,
	.ग_लिखो_block	= frpw_ग_लिखो_block,
	.पढ़ो_block	= frpw_पढ़ो_block,
	.connect	= frpw_connect,
	.disconnect	= frpw_disconnect,
	.test_proto	= frpw_test_proto,
	.log_adapter	= frpw_log_adapter,
पूर्ण;

अटल पूर्णांक __init frpw_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&frpw);
पूर्ण

अटल व्योम __निकास frpw_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&frpw);
पूर्ण

MODULE_LICENSE("GPL");
module_init(frpw_init)
module_निकास(frpw_निकास)
