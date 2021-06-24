<शैली गुरु>
/*
 * linux/drivers/video/nvidia/nv_of.c
 *
 * Copyright 2004 Antonino A. Daplas <adaplas @pol.net>
 *
 * Based on rivafb-i2c.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/पन.स>

#समावेश "nv_type.h"
#समावेश "nv_local.h"
#समावेश "nv_proto.h"

#समावेश "../edid.h"

पूर्णांक nvidia_probe_of_connector(काष्ठा fb_info *info, पूर्णांक conn, u8 **out_edid)
अणु
	काष्ठा nvidia_par *par = info->par;
	काष्ठा device_node *parent, *dp;
	स्थिर अचिन्हित अक्षर *pedid = शून्य;
	अटल अक्षर *propnames[] = अणु
		"DFP,EDID", "LCD,EDID", "EDID", "EDID1",
		"EDID,B", "EDID,A", शून्य पूर्ण;
	पूर्णांक i;

	parent = pci_device_to_OF_node(par->pci_dev);
	अगर (parent == शून्य)
		वापस -1;
	अगर (par->twoHeads) अणु
		स्थिर अक्षर *pname;
		पूर्णांक len;

		क्रम_each_child_of_node(parent, dp) अणु
			pname = of_get_property(dp, "name", शून्य);
			अगर (!pname)
				जारी;
			len = म_माप(pname);
			अगर ((pname[len-1] == 'A' && conn == 1) ||
			    (pname[len-1] == 'B' && conn == 2)) अणु
				क्रम (i = 0; propnames[i] != शून्य; ++i) अणु
					pedid = of_get_property(dp,
							propnames[i], शून्य);
					अगर (pedid != शून्य)
						अवरोध;
				पूर्ण
				of_node_put(dp);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (pedid == शून्य) अणु
		क्रम (i = 0; propnames[i] != शून्य; ++i) अणु
			pedid = of_get_property(parent, propnames[i], शून्य);
			अगर (pedid != शून्य)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (pedid) अणु
		*out_edid = kmemdup(pedid, EDID_LENGTH, GFP_KERNEL);
		अगर (*out_edid == शून्य)
			वापस -1;
		prपूर्णांकk(KERN_DEBUG "nvidiafb: Found OF EDID for head %d\n", conn);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
