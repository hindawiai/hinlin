<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * idprom.c: Routines to load the idprom पूर्णांकo kernel addresses and
 *           पूर्णांकerpret the data contained within.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Sun3/3x models added by David Monro (davidm@psrg.cs.usyd.edu.au)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/machines.h>  /* Fun with Sun released architectures. */

काष्ठा idprom *idprom;
EXPORT_SYMBOL(idprom);

अटल काष्ठा idprom idprom_buffer;

/* Here is the master table of Sun machines which use some implementation
 * of the Sparc CPU and have a meaningful IDPROM machtype value that we
 * know about.  See यंत्र-sparc/machines.h क्रम empirical स्थिरants.
 */
अटल काष्ठा Sun_Machine_Models Sun_Machines[NUM_SUN_MACHINES] = अणु
/* First, Sun3's */
    अणु .name = "Sun 3/160 Series",	.id_machtype = (SM_SUN3 | SM_3_160) पूर्ण,
    अणु .name = "Sun 3/50",		.id_machtype = (SM_SUN3 | SM_3_50) पूर्ण,
    अणु .name = "Sun 3/260 Series",	.id_machtype = (SM_SUN3 | SM_3_260) पूर्ण,
    अणु .name = "Sun 3/110 Series",	.id_machtype = (SM_SUN3 | SM_3_110) पूर्ण,
    अणु .name = "Sun 3/60",		.id_machtype = (SM_SUN3 | SM_3_60) पूर्ण,
    अणु .name = "Sun 3/E",		.id_machtype = (SM_SUN3 | SM_3_E) पूर्ण,
/* Now, Sun3x's */
    अणु .name = "Sun 3/460 Series",	.id_machtype = (SM_SUN3X | SM_3_460) पूर्ण,
    अणु .name = "Sun 3/80",		.id_machtype = (SM_SUN3X | SM_3_80) पूर्ण,
/* Then, Sun4's */
// अणु .name = "Sun 4/100 Series",	.id_machtype = (SM_SUN4 | SM_4_110) पूर्ण,
// अणु .name = "Sun 4/200 Series",	.id_machtype = (SM_SUN4 | SM_4_260) पूर्ण,
// अणु .name = "Sun 4/300 Series",	.id_machtype = (SM_SUN4 | SM_4_330) पूर्ण,
// अणु .name = "Sun 4/400 Series",	.id_machtype = (SM_SUN4 | SM_4_470) पूर्ण,
/* And now, Sun4c's */
// अणु .name = "Sun4c SparcStation 1",	.id_machtype = (SM_SUN4C | SM_4C_SS1) पूर्ण,
// अणु .name = "Sun4c SparcStation IPC",	.id_machtype = (SM_SUN4C | SM_4C_IPC) पूर्ण,
// अणु .name = "Sun4c SparcStation 1+",	.id_machtype = (SM_SUN4C | SM_4C_SS1PLUS) पूर्ण,
// अणु .name = "Sun4c SparcStation SLC",	.id_machtype = (SM_SUN4C | SM_4C_SLC) पूर्ण,
// अणु .name = "Sun4c SparcStation 2",	.id_machtype = (SM_SUN4C | SM_4C_SS2) पूर्ण,
// अणु .name = "Sun4c SparcStation ELC",	.id_machtype = (SM_SUN4C | SM_4C_ELC) पूर्ण,
// अणु .name = "Sun4c SparcStation IPX",	.id_machtype = (SM_SUN4C | SM_4C_IPX) पूर्ण,
/* Finally, early Sun4m's */
// अणु .name = "Sun4m SparcSystem600",	.id_machtype = (SM_SUN4M | SM_4M_SS60) पूर्ण,
// अणु .name = "Sun4m SparcStation10/20",	.id_machtype = (SM_SUN4M | SM_4M_SS50) पूर्ण,
// अणु .name = "Sun4m SparcStation5",	.id_machtype = (SM_SUN4M | SM_4M_SS40) पूर्ण,
/* One entry क्रम the OBP arch's which are sun4d, sun4e, and newer sun4m's */
// अणु .name = "Sun4M OBP based system",	.id_machtype = (SM_SUN4M_OBP | 0x0) पूर्ण
पूर्ण;

अटल व्योम __init display_प्रणाली_type(अचिन्हित अक्षर machtype)
अणु
	रेजिस्टर पूर्णांक i;

	क्रम (i = 0; i < NUM_SUN_MACHINES; i++) अणु
		अगर(Sun_Machines[i].id_machtype == machtype) अणु
			अगर (machtype != (SM_SUN4M_OBP | 0x00))
				pr_info("TYPE: %s\n", Sun_Machines[i].name);
			अन्यथा अणु
#अगर 0
				अक्षर sysname[128];

				prom_getproperty(prom_root_node, "banner-name",
						 sysname, माप(sysname));
				pr_info("TYPE: %s\n", sysname);
#पूर्ण_अगर
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	prom_म_लिखो("IDPROM: Bogus id_machtype value, 0x%x\n", machtype);
	prom_halt();
पूर्ण

व्योम sun3_get_model(अचिन्हित अक्षर* model)
अणु
	रेजिस्टर पूर्णांक i;

	क्रम (i = 0; i < NUM_SUN_MACHINES; i++) अणु
		अगर(Sun_Machines[i].id_machtype == idprom->id_machtype) अणु
		        म_नकल(model, Sun_Machines[i].name);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण



/* Calculate the IDPROM checksum (xor of the data bytes). */
अटल अचिन्हित अक्षर __init calc_idprom_cksum(काष्ठा idprom *idprom)
अणु
	अचिन्हित अक्षर cksum, i, *ptr = (अचिन्हित अक्षर *)idprom;

	क्रम (i = cksum = 0; i <= 0x0E; i++)
		cksum ^= *ptr++;

	वापस cksum;
पूर्ण

/* Create a local IDPROM copy, verअगरy पूर्णांकegrity, and display inक्रमmation. */
व्योम __init idprom_init(व्योम)
अणु
	prom_get_idprom((अक्षर *) &idprom_buffer, माप(idprom_buffer));

	idprom = &idprom_buffer;

	अगर (idprom->id_क्रमmat != 0x01)  अणु
		prom_म_लिखो("IDPROM: Unknown format type!\n");
		prom_halt();
	पूर्ण

	अगर (idprom->id_cksum != calc_idprom_cksum(idprom)) अणु
		prom_म_लिखो("IDPROM: Checksum failure (nvram=%x, calc=%x)!\n",
			    idprom->id_cksum, calc_idprom_cksum(idprom));
		prom_halt();
	पूर्ण

	display_प्रणाली_type(idprom->id_machtype);

	pr_info("Ethernet address: %pM\n", idprom->id_ethaddr);
पूर्ण
