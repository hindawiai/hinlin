<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * console.c: Routines that deal with sending and receiving IO
 *            to/from the current console device using the PROM.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/माला.स>

/* Non blocking get अक्षरacter from console input device, वापसs -1
 * अगर no input was taken.  This can be used क्रम polling.
 */
पूर्णांक
prom_nbअक्षर_लो(व्योम)
अणु
	पूर्णांक i = -1;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
		i = (*(romvec->pv_nbअक्षर_लो))();
	local_irq_restore(flags);
	वापस i; /* Ugh, we could spin क्रमever on unsupported proms ;( */
पूर्ण

/* Non blocking put अक्षरacter to console device, वापसs -1 अगर
 * unsuccessful.
 */
पूर्णांक
prom_nbअक्षर_दो(अक्षर c)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i = -1;

	local_irq_save(flags);
		i = (*(romvec->pv_nbअक्षर_दो))(c);
	local_irq_restore(flags);
	वापस i; /* Ugh, we could spin क्रमever on unsupported proms ;( */
पूर्ण

/* Blocking version of get अक्षरacter routine above. */
अक्षर
prom_अक्षर_लो(व्योम)
अणु
	पूर्णांक अक्षरacter;
	जबतक((अक्षरacter = prom_nbअक्षर_लो()) == -1) ;
	वापस (अक्षर) अक्षरacter;
पूर्ण

/* Blocking version of put अक्षरacter routine above. */
व्योम
prom_अक्षर_दो(अक्षर c)
अणु
	जबतक(prom_nbअक्षर_दो(c) == -1) ;
	वापस;
पूर्ण

/* Query क्रम input device type */
#अगर 0
क्रमागत prom_input_device
prom_query_input_device()
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक st_p;
	अक्षर propb[64];
	अक्षर *p;

	चयन(prom_vers) अणु
	हाल PROM_V0:
	हाल PROM_V2:
	शेष:
		चयन(*romvec->pv_मानक_निवेश) अणु
		हाल PROMDEV_KBD:	वापस PROMDEV_IKBD;
		हाल PROMDEV_TTYA:	वापस PROMDEV_ITTYA;
		हाल PROMDEV_TTYB:	वापस PROMDEV_ITTYB;
		शेष:
			वापस PROMDEV_I_UNK;
		पूर्ण;
	हाल PROM_V3:
	हाल PROM_P1275:
		local_irq_save(flags);
		st_p = (*romvec->pv_v2devops.v2_inst2pkg)(*romvec->pv_v2bootargs.fd_मानक_निवेश);
		__यंत्र__ __अस्थिर__("ld [%0], %%g6\n\t" : :
				     "r" (&current_set[smp_processor_id()]) :
				     "memory");
		local_irq_restore(flags);
		अगर(prom_node_has_property(st_p, "keyboard"))
			वापस PROMDEV_IKBD;
		prom_getproperty(st_p, "device_type", propb, माप(propb));
		अगर(म_भेदन(propb, "serial", माप("serial")))
			वापस PROMDEV_I_UNK;
		prom_getproperty(prom_root_node, "stdin-path", propb, माप(propb));
		p = propb;
		जबतक(*p) p++; p -= 2;
		अगर(p[0] == ':') अणु
			अगर(p[1] == 'a')
				वापस PROMDEV_ITTYA;
			अन्यथा अगर(p[1] == 'b')
				वापस PROMDEV_ITTYB;
		पूर्ण
		वापस PROMDEV_I_UNK;
	पूर्ण;
पूर्ण
#पूर्ण_अगर

/* Query क्रम output device type */

#अगर 0
क्रमागत prom_output_device
prom_query_output_device()
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक st_p;
	अक्षर propb[64];
	अक्षर *p;
	पूर्णांक propl;

	चयन(prom_vers) अणु
	हाल PROM_V0:
		चयन(*romvec->pv_मानक_निवेश) अणु
		हाल PROMDEV_SCREEN:	वापस PROMDEV_OSCREEN;
		हाल PROMDEV_TTYA:	वापस PROMDEV_OTTYA;
		हाल PROMDEV_TTYB:	वापस PROMDEV_OTTYB;
		पूर्ण;
		अवरोध;
	हाल PROM_V2:
	हाल PROM_V3:
	हाल PROM_P1275:
		local_irq_save(flags);
		st_p = (*romvec->pv_v2devops.v2_inst2pkg)(*romvec->pv_v2bootargs.fd_मानक_निकास);
		__यंत्र__ __अस्थिर__("ld [%0], %%g6\n\t" : :
				     "r" (&current_set[smp_processor_id()]) :
				     "memory");
		local_irq_restore(flags);
		propl = prom_getproperty(st_p, "device_type", propb, माप(propb));
		अगर (propl >= 0 && propl == माप("display") &&
			म_भेदन("display", propb, माप("display")) == 0)
		अणु
			वापस PROMDEV_OSCREEN;
		पूर्ण
		अगर(prom_vers == PROM_V3) अणु
			अगर(म_भेदन("serial", propb, माप("serial")))
				वापस PROMDEV_O_UNK;
			prom_getproperty(prom_root_node, "stdout-path", propb, माप(propb));
			p = propb;
			जबतक(*p) p++; p -= 2;
			अगर(p[0]==':') अणु
				अगर(p[1] == 'a')
					वापस PROMDEV_OTTYA;
				अन्यथा अगर(p[1] == 'b')
					वापस PROMDEV_OTTYB;
			पूर्ण
			वापस PROMDEV_O_UNK;
		पूर्ण अन्यथा अणु
			/* This works on SS-2 (an early OpenFirmware) still. */
			चयन(*romvec->pv_मानक_निवेश) अणु
			हाल PROMDEV_TTYA:	वापस PROMDEV_OTTYA;
			हाल PROMDEV_TTYB:	वापस PROMDEV_OTTYB;
			पूर्ण;
		पूर्ण
		अवरोध;
	पूर्ण;
	वापस PROMDEV_O_UNK;
पूर्ण
#पूर्ण_अगर
