<शैली गुरु>
/*
	backpack.c (c) 2001 Micro Solutions Inc.
		Released under the terms of the GNU General Public license

	backpack.c is a low-level protocol driver क्रम the Micro Solutions
		"BACKPACK" parallel port IDE adapter
		(Works on Series 6 drives)

	Written by: Ken Hahn     (linux-dev@micro-solutions.com)
	            Clive Turvey (linux-dev@micro-solutions.com)

*/

/*
   This is Ken's linux wrapper क्रम the PPC library
   Version 1.0.0 is the backpack driver क्रम which source is not available
   Version 2.0.0 is the first to have source released 
   Version 2.0.1 is the "Cox-ified" source code 
   Version 2.0.2 - fixed version string usage, and made ppc functions अटल 
*/


#घोषणा BACKPACK_VERSION "2.0.2"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/parport.h>

#समावेश "ppc6lnx.c"
#समावेश "paride.h"

/* PARAMETERS */
अटल bool verbose; /* set this to 1 to see debugging messages and whatnot */
 

#घोषणा PPCSTRUCT(pi) ((Interface *)(pi->निजी))

/****************************************************************/
/*
 ATAPI CDROM DRIVE REGISTERS
*/
#घोषणा ATAPI_DATA       0      /* data port                  */
#घोषणा ATAPI_ERROR      1      /* error रेजिस्टर (पढ़ो)      */
#घोषणा ATAPI_FEATURES   1      /* feature रेजिस्टर (ग_लिखो)   */
#घोषणा ATAPI_INT_REASON 2      /* पूर्णांकerrupt reason रेजिस्टर  */
#घोषणा ATAPI_COUNT_LOW  4      /* byte count रेजिस्टर (low)  */
#घोषणा ATAPI_COUNT_HIGH 5      /* byte count रेजिस्टर (high) */
#घोषणा ATAPI_DRIVE_SEL  6      /* drive select रेजिस्टर      */
#घोषणा ATAPI_STATUS     7      /* status port (पढ़ो)         */
#घोषणा ATAPI_COMMAND    7      /* command port (ग_लिखो)       */
#घोषणा ATAPI_ALT_STATUS 0x0e /* alternate status reg (पढ़ो) */
#घोषणा ATAPI_DEVICE_CONTROL 0x0e /* device control (ग_लिखो)   */
/****************************************************************/

अटल पूर्णांक bpck6_पढ़ो_regr(PIA *pi, पूर्णांक cont, पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक out;

	/* check क्रम bad settings */
	अगर (reg<0 || reg>7 || cont<0 || cont>2)
	अणु
		वापस(-1);
	पूर्ण
	out=ppc6_rd_port(PPCSTRUCT(pi),cont?reg|8:reg);
	वापस(out);
पूर्ण

अटल व्योम bpck6_ग_लिखो_regr(PIA *pi, पूर्णांक cont, पूर्णांक reg, पूर्णांक val)
अणु
	/* check क्रम bad settings */
	अगर (reg>=0 && reg<=7 && cont>=0 && cont<=1)
	अणु
		ppc6_wr_port(PPCSTRUCT(pi),cont?reg|8:reg,(u8)val);
	पूर्ण
पूर्ण

अटल व्योम bpck6_ग_लिखो_block( PIA *pi, अक्षर * buf, पूर्णांक len )
अणु
	ppc6_wr_port16_blk(PPCSTRUCT(pi),ATAPI_DATA,buf,(u32)len>>1); 
पूर्ण

अटल व्योम bpck6_पढ़ो_block( PIA *pi, अक्षर * buf, पूर्णांक len )
अणु
	ppc6_rd_port16_blk(PPCSTRUCT(pi),ATAPI_DATA,buf,(u32)len>>1);
पूर्ण

अटल व्योम bpck6_connect ( PIA *pi  )
अणु
	अगर(verbose)
	अणु
		prपूर्णांकk(KERN_DEBUG "connect\n");
	पूर्ण

	अगर(pi->mode >=2)
  	अणु
		PPCSTRUCT(pi)->mode=4+pi->mode-2;	
	पूर्ण
	अन्यथा अगर(pi->mode==1)
	अणु
		PPCSTRUCT(pi)->mode=3;	
	पूर्ण
	अन्यथा
	अणु
		PPCSTRUCT(pi)->mode=1;		
	पूर्ण

	ppc6_खोलो(PPCSTRUCT(pi));  
	ppc6_wr_extout(PPCSTRUCT(pi),0x3);
पूर्ण

अटल व्योम bpck6_disconnect ( PIA *pi )
अणु
	अगर(verbose)
	अणु
		prपूर्णांकk("disconnect\n");
	पूर्ण
	ppc6_wr_extout(PPCSTRUCT(pi),0x0);
	ppc6_बंद(PPCSTRUCT(pi));
पूर्ण

अटल पूर्णांक bpck6_test_port ( PIA *pi )   /* check क्रम 8-bit port */
अणु
	अगर(verbose)
	अणु
		prपूर्णांकk(KERN_DEBUG "PARPORT indicates modes=%x for lp=0x%lx\n",
               		((काष्ठा pardevice*)(pi->pardev))->port->modes,
			((काष्ठा pardevice *)(pi->pardev))->port->base); 
	पूर्ण

	/*copy over duplicate stuff.. initialize state info*/
	PPCSTRUCT(pi)->ppc_id=pi->unit;
	PPCSTRUCT(pi)->lpt_addr=pi->port;

	/* look at the parport device to see अगर what modes we can use */
	अगर(((काष्ठा pardevice *)(pi->pardev))->port->modes & 
		(PARPORT_MODE_EPP)
          )
	अणु
		वापस 5; /* Can करो EPP*/
	पूर्ण
	अन्यथा अगर(((काष्ठा pardevice *)(pi->pardev))->port->modes & 
			(PARPORT_MODE_TRISTATE)
               )
	अणु
		वापस 2;
	पूर्ण
	अन्यथा /*Just flat SPP*/
	अणु
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक bpck6_probe_unit ( PIA *pi )
अणु
	पूर्णांक out;

	अगर(verbose)
	अणु
		prपूर्णांकk(KERN_DEBUG "PROBE UNIT %x on port:%x\n",pi->unit,pi->port);
	पूर्ण

	/*SET PPC UNIT NUMBER*/
	PPCSTRUCT(pi)->ppc_id=pi->unit;

	/*LOWER DOWN TO UNIसूचीECTIONAL*/
	PPCSTRUCT(pi)->mode=1;		

	out=ppc6_खोलो(PPCSTRUCT(pi));

	अगर(verbose)
	अणु
		prपूर्णांकk(KERN_DEBUG "ppc_open returned %2x\n",out);
	पूर्ण

  	अगर(out)
 	अणु
		ppc6_बंद(PPCSTRUCT(pi));
		अगर(verbose)
		अणु
			prपूर्णांकk(KERN_DEBUG "leaving probe\n");
		पूर्ण
               वापस(1);
	पूर्ण
  	अन्यथा
  	अणु
		अगर(verbose)
		अणु
			prपूर्णांकk(KERN_DEBUG "Failed open\n");
		पूर्ण
    		वापस(0);
  	पूर्ण
पूर्ण

अटल व्योम bpck6_log_adapter( PIA *pi, अक्षर * scratch, पूर्णांक verbose )
अणु
	अक्षर *mode_string[5]=
		अणु"4-bit","8-bit","EPP-8","EPP-16","EPP-32"पूर्ण;

	prपूर्णांकk("%s: BACKPACK Protocol Driver V"BACKPACK_VERSION"\n",pi->device);
	prपूर्णांकk("%s: Copyright 2001 by Micro Solutions, Inc., DeKalb IL.\n",pi->device);
	prपूर्णांकk("%s: BACKPACK %s, Micro Solutions BACKPACK Drive at 0x%x\n",
		pi->device,BACKPACK_VERSION,pi->port);
	prपूर्णांकk("%s: Unit: %d Mode:%d (%s) Delay %d\n",pi->device,
		pi->unit,pi->mode,mode_string[pi->mode],pi->delay);
पूर्ण

अटल पूर्णांक bpck6_init_proto(PIA *pi)
अणु
	Interface *p = kzalloc(माप(Interface), GFP_KERNEL);

	अगर (p) अणु
		pi->निजी = (अचिन्हित दीर्घ)p;
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: ERROR COULDN'T ALLOCATE MEMORY\n", pi->device); 
	वापस -1;
पूर्ण

अटल व्योम bpck6_release_proto(PIA *pi)
अणु
	kमुक्त((व्योम *)(pi->निजी)); 
पूर्ण

अटल काष्ठा pi_protocol bpck6 = अणु
	.owner		= THIS_MODULE,
	.name		= "bpck6",
	.max_mode	= 5,
	.epp_first	= 2, /* 2-5 use epp (need 8 ports) */
	.max_units	= 255,
	.ग_लिखो_regr	= bpck6_ग_लिखो_regr,
	.पढ़ो_regr	= bpck6_पढ़ो_regr,
	.ग_लिखो_block	= bpck6_ग_लिखो_block,
	.पढ़ो_block	= bpck6_पढ़ो_block,
	.connect	= bpck6_connect,
	.disconnect	= bpck6_disconnect,
	.test_port	= bpck6_test_port,
	.probe_unit	= bpck6_probe_unit,
	.log_adapter	= bpck6_log_adapter,
	.init_proto	= bpck6_init_proto,
	.release_proto	= bpck6_release_proto,
पूर्ण;

अटल पूर्णांक __init bpck6_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "bpck6: BACKPACK Protocol Driver V"BACKPACK_VERSION"\n");
	prपूर्णांकk(KERN_INFO "bpck6: Copyright 2001 by Micro Solutions, Inc., DeKalb IL. USA\n");
	अगर(verbose)
		prपूर्णांकk(KERN_DEBUG "bpck6: verbose debug enabled.\n");
	वापस paride_रेजिस्टर(&bpck6);
पूर्ण

अटल व्योम __निकास bpck6_निकास(व्योम)
अणु
	paride_unरेजिस्टर(&bpck6);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Micro Solutions Inc.");
MODULE_DESCRIPTION("BACKPACK Protocol module, compatible with PARIDE");
module_param(verbose, bool, 0644);
module_init(bpck6_init)
module_निकास(bpck6_निकास)
