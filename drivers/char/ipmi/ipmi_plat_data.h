<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

/*
 * Generic code to add IPMI platक्रमm devices.
 */

#समावेश <linux/ipmi.h>

क्रमागत ipmi_plat_पूर्णांकerface_type अणु IPMI_PLAT_IF_SI, IPMI_PLAT_IF_SSIF पूर्ण;

काष्ठा ipmi_plat_data अणु
	क्रमागत ipmi_plat_पूर्णांकerface_type अगरtype;
	अचिन्हित पूर्णांक type; /* si_type क्रम si, SI_INVALID क्रम others */
	अचिन्हित पूर्णांक space; /* addr_space क्रम si, पूर्णांकf# क्रम ssअगर. */
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक regspacing;
	अचिन्हित पूर्णांक regsize;
	अचिन्हित पूर्णांक regshअगरt;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक slave_addr;
	क्रमागत ipmi_addr_src addr_source;
पूर्ण;

काष्ठा platक्रमm_device *ipmi_platक्रमm_add(स्थिर अक्षर *name, अचिन्हित पूर्णांक inst,
					  काष्ठा ipmi_plat_data *p);
