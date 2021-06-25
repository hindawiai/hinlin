<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * idprom.c: Routines to load the idprom पूर्णांकo kernel addresses and
 *           पूर्णांकerpret the data contained within.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/idprom.h>

काष्ठा idprom *idprom;
EXPORT_SYMBOL(idprom);

अटल काष्ठा idprom idprom_buffer;

#अगर_घोषित CONFIG_SPARC32
#समावेश <यंत्र/machines.h>  /* Fun with Sun released architectures. */

/* Here is the master table of Sun machines which use some implementation
 * of the Sparc CPU and have a meaningful IDPROM machtype value that we
 * know about.  See यंत्र-sparc/machines.h क्रम empirical स्थिरants.
 */
अटल काष्ठा Sun_Machine_Models Sun_Machines[] = अणु
/* First, Leon */
अणु .name = "Leon3 System-on-a-Chip",  .id_machtype = (M_LEON | M_LEON3_SOC) पूर्ण,
/* Finally, early Sun4m's */
अणु .name = "Sun4m SparcSystem600",    .id_machtype = (SM_SUN4M | SM_4M_SS60) पूर्ण,
अणु .name = "Sun4m SparcStation10/20", .id_machtype = (SM_SUN4M | SM_4M_SS50) पूर्ण,
अणु .name = "Sun4m SparcStation5",     .id_machtype = (SM_SUN4M | SM_4M_SS40) पूर्ण,
/* One entry क्रम the OBP arch's which are sun4d, sun4e, and newer sun4m's */
अणु .name = "Sun4M OBP based system",  .id_machtype = (SM_SUN4M_OBP | 0x0) पूर्ण पूर्ण;

अटल व्योम __init display_प्रणाली_type(अचिन्हित अक्षर machtype)
अणु
	अक्षर sysname[128];
	रेजिस्टर पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(Sun_Machines); i++) अणु
		अगर (Sun_Machines[i].id_machtype == machtype) अणु
			अगर (machtype != (SM_SUN4M_OBP | 0x00) ||
			    prom_getproperty(prom_root_node, "banner-name",
					     sysname, माप(sysname)) <= 0)
				prपूर्णांकk(KERN_WARNING "TYPE: %s\n",
				       Sun_Machines[i].name);
			अन्यथा
				prपूर्णांकk(KERN_WARNING "TYPE: %s\n", sysname);
			वापस;
		पूर्ण
	पूर्ण

	prom_म_लिखो("IDPROM: Warning, bogus id_machtype value, 0x%x\n", machtype);
पूर्ण
#अन्यथा
अटल व्योम __init display_प्रणाली_type(अचिन्हित अक्षर machtype)
अणु
पूर्ण
#पूर्ण_अगर

अचिन्हित अक्षर *arch_get_platक्रमm_mac_address(व्योम)
अणु
	वापस idprom->id_ethaddr;
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

	अगर (idprom->id_क्रमmat != 0x01)
		prom_म_लिखो("IDPROM: Warning, unknown format type!\n");

	अगर (idprom->id_cksum != calc_idprom_cksum(idprom))
		prom_म_लिखो("IDPROM: Warning, checksum failure (nvram=%x, calc=%x)!\n",
			    idprom->id_cksum, calc_idprom_cksum(idprom));

	display_प्रणाली_type(idprom->id_machtype);

	prपूर्णांकk(KERN_WARNING "Ethernet address: %pM\n", idprom->id_ethaddr);
पूर्ण
