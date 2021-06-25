<शैली गुरु>
/* 
        comm.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

	comm.c is a low-level protocol driver क्रम some older models
	of the DataStor "Commuter" parallel to IDE adapter.  Some of
	the parallel port devices marketed by Arista currently
	use this adapter.
*/

/* Changes:

	1.01	GRG 1998.05.05  init_proto, release_proto

*/

#घोषणा COMM_VERSION      "1.01"

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
*/

#घोषणा j44(a,b)	(((a>>3)&0x0f)|((b<<1)&0xf0))

#घोषणा P1	w2(5);w2(0xd);w2(0xd);w2(5);w2(4);
#घोषणा P2	w2(5);w2(7);w2(7);w2(5);w2(4);

/* cont = 0 - access the IDE रेजिस्टर file 
   cont = 1 - access the IDE command set 
*/

अटल पूर्णांक  cont_map[2] = अणु 0x08, 0x10 पूर्ण;

अटल पूर्णांक comm_पढ़ो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr )

अणु       पूर्णांक     l, h, r;

        r = regr + cont_map[cont];

        चयन (pi->mode)  अणु

        हाल 0: w0(r); P1; w0(0);
        	w2(6); l = r1(); w0(0x80); h = r1(); w2(4);
                वापस j44(l,h);

        हाल 1: w0(r+0x20); P1; 
        	w0(0); w2(0x26); h = r0(); w2(4);
                वापस h;

	हाल 2:
	हाल 3:
        हाल 4: w3(r+0x20); (व्योम)r1();
        	w2(0x24); h = r4(); w2(4);
                वापस h;

        पूर्ण
        वापस -1;
पूर्ण       

अटल व्योम comm_ग_लिखो_regr( PIA *pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val )

अणु       पूर्णांक  r;

        r = regr + cont_map[cont];

        चयन (pi->mode)  अणु

        हाल 0:
        हाल 1: w0(r); P1; w0(val); P2;
		अवरोध;

	हाल 2:
	हाल 3:
        हाल 4: w3(r); (व्योम)r1(); w4(val);
                अवरोध;
        पूर्ण
पूर्ण

अटल व्योम comm_connect ( PIA *pi  )

अणु       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
        w2(4); w0(0xff); w2(6);
        w2(4); w0(0xaa); w2(6);
        w2(4); w0(0x00); w2(6);
        w2(4); w0(0x87); w2(6);
        w2(4); w0(0xe0); w2(0xc); w2(0xc); w2(4);
पूर्ण

अटल व्योम comm_disconnect ( PIA *pi )

अणु       w2(0); w2(0); w2(0); w2(4); 
	w0(pi->saved_r0);
        w2(pi->saved_r2);
पूर्ण 

अटल व्योम comm_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक     i, l, h;

        चयन (pi->mode) अणु
        
        हाल 0: w0(0x48); P1;
                क्रम(i=0;i<count;i++) अणु
                        w0(0); w2(6); l = r1();
                        w0(0x80); h = r1(); w2(4);
                        buf[i] = j44(l,h);
                पूर्ण
                अवरोध;

        हाल 1: w0(0x68); P1; w0(0);
                क्रम(i=0;i<count;i++) अणु
                        w2(0x26); buf[i] = r0(); w2(0x24);
                पूर्ण
		w2(4);
		अवरोध;
		
	हाल 2: w3(0x68); (व्योम)r1(); w2(0x24);
		क्रम (i=0;i<count;i++) buf[i] = r4();
		w2(4);
		अवरोध;

        हाल 3: w3(0x68); (व्योम)r1(); w2(0x24);
                क्रम (i=0;i<count/2;i++) ((u16 *)buf)[i] = r4w();
                w2(4);
                अवरोध;

        हाल 4: w3(0x68); (व्योम)r1(); w2(0x24);
                क्रम (i=0;i<count/4;i++) ((u32 *)buf)[i] = r4l();
                w2(4);
                अवरोध;
		
	पूर्ण
पूर्ण

/* NB: Watch out क्रम the byte swapped ग_लिखोs ! */

अटल व्योम comm_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक count )

अणु       पूर्णांक	k;

        चयन (pi->mode) अणु

        हाल 0:
        हाल 1: w0(0x68); P1;
        	क्रम (k=0;k<count;k++) अणु
                        w2(5); w0(buf[k^1]); w2(7);
                पूर्ण
                w2(5); w2(4);
                अवरोध;

        हाल 2: w3(0x48); (व्योम)r1();
                क्रम (k=0;k<count;k++) w4(buf[k^1]);
                अवरोध;

        हाल 3: w3(0x48); (व्योम)r1();
                क्रम (k=0;k<count/2;k++) w4w(pi_swab16(buf,k));
                अवरोध;

        हाल 4: w3(0x48); (व्योम)r1();
                क्रम (k=0;k<count/4;k++) w4l(pi_swab32(buf,k));
                अवरोध;


        पूर्ण
पूर्ण

अटल व्योम comm_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )

अणु       अक्षर    *mode_string[5] = अणु"4-bit","8-bit","EPP-8","EPP-16","EPP-32"पूर्ण;

        prपूर्णांकk("%s: comm %s, DataStor Commuter at 0x%x, ",
                pi->device,COMM_VERSION,pi->port);
        prपूर्णांकk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

पूर्ण

अटल काष्ठा pi_protocol comm = अणु
	.owner		= THIS_MODULE,
	.name		= "comm",
	.max_mode	= 5,
	.epp_first	= 2,
	.शेष_delay	= 1,
	.max_units	= 1,
	.ग_लिखो_regr	= comm_ग_लिखो_regr,
	.पढ़ो_regr	= comm_पढ़ो_regr,
	.ग_लिखो_block	= comm_ग_लिखो_block,
	.पढ़ो_block	= comm_पढ़ो_block,
	.connect	= comm_connect,
	.disconnect	= comm_disconnect,
	.log_adapter	= comm_log_adapter,
पूर्ण;

अटल पूर्णांक __init comm_init(व्योम)
अणु
	वापस paride_रेजिस्टर(&comm);
पूर्ण

अटल व्योम __निकास comm_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&comm);
पूर्ण

MODULE_LICENSE("GPL");
module_init(comm_init)
module_निकास(comm_निकास)
