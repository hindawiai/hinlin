<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 IBM Corporation.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "io.h"
#समावेश <libfdt.h>
#समावेश "../include/asm/opal-api.h"

/* Global OPAL काष्ठा used by opal-call.S */
काष्ठा opal अणु
	u64 base;
	u64 entry;
पूर्ण opal;

अटल u32 opal_con_id;

/* see opal-wrappers.S */
पूर्णांक64_t opal_console_ग_लिखो(पूर्णांक64_t term_number, u64 *length, स्थिर u8 *buffer);
पूर्णांक64_t opal_console_पढ़ो(पूर्णांक64_t term_number, uपूर्णांक64_t *length, u8 *buffer);
पूर्णांक64_t opal_console_ग_लिखो_buffer_space(uपूर्णांक64_t term_number, uपूर्णांक64_t *length);
पूर्णांक64_t opal_console_flush(uपूर्णांक64_t term_number);
पूर्णांक64_t opal_poll_events(uपूर्णांक64_t *outstanding_event_mask);

व्योम opal_kentry(अचिन्हित दीर्घ fdt_addr, व्योम *vmlinux_addr);

अटल पूर्णांक opal_con_खोलो(व्योम)
अणु
	/*
	 * When OPAL loads the boot kernel it stashes the OPAL base and entry
	 * address in r8 and r9 so the kernel can use the OPAL console
	 * beक्रमe unflattening the devicetree. While executing the wrapper will
	 * probably trash r8 and r9 so this kentry hook restores them beक्रमe
	 * entering the decompressed kernel.
	 */
	platक्रमm_ops.kentry = opal_kentry;
	वापस 0;
पूर्ण

अटल व्योम opal_con_अ_दो(अचिन्हित अक्षर c)
अणु
	पूर्णांक64_t rc;
	uपूर्णांक64_t olen, len;

	करो अणु
		rc = opal_console_ग_लिखो_buffer_space(opal_con_id, &olen);
		len = be64_to_cpu(olen);
		अगर (rc)
			वापस;
		opal_poll_events(शून्य);
	पूर्ण जबतक (len < 1);


	olen = cpu_to_be64(1);
	opal_console_ग_लिखो(opal_con_id, &olen, &c);
पूर्ण

अटल व्योम opal_con_बंद(व्योम)
अणु
	opal_console_flush(opal_con_id);
पूर्ण

अटल व्योम opal_init(व्योम)
अणु
	व्योम *opal_node;

	opal_node = finddevice("/ibm,opal");
	अगर (!opal_node)
		वापस;
	अगर (getprop(opal_node, "opal-base-address", &opal.base, माप(u64)) < 0)
		वापस;
	opal.base = be64_to_cpu(opal.base);
	अगर (getprop(opal_node, "opal-entry-address", &opal.entry, माप(u64)) < 0)
		वापस;
	opal.entry = be64_to_cpu(opal.entry);
पूर्ण

पूर्णांक opal_console_init(व्योम *devp, काष्ठा serial_console_data *scdp)
अणु
	opal_init();

	अगर (devp) अणु
		पूर्णांक n = getprop(devp, "reg", &opal_con_id, माप(u32));
		अगर (n != माप(u32))
			वापस -1;
		opal_con_id = be32_to_cpu(opal_con_id);
	पूर्ण अन्यथा
		opal_con_id = 0;

	scdp->खोलो = opal_con_खोलो;
	scdp->अ_दो = opal_con_अ_दो;
	scdp->बंद = opal_con_बंद;

	वापस 0;
पूर्ण
