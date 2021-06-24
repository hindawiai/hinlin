<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV nvram code.
 *
 * Copyright 2011 IBM Corp.
 */

#घोषणा DEBUG

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/machdep.h>

अटल अचिन्हित पूर्णांक nvram_size;

अटल sमाप_प्रकार opal_nvram_size(व्योम)
अणु
	वापस nvram_size;
पूर्ण

अटल sमाप_प्रकार opal_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	s64 rc;
	पूर्णांक off;

	अगर (*index >= nvram_size)
		वापस 0;
	off = *index;
	अगर ((off + count) > nvram_size)
		count = nvram_size - off;
	rc = opal_पढ़ो_nvram(__pa(buf), count, off);
	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;
	*index += count;
	वापस count;
पूर्ण

/*
 * This can be called in the panic path with पूर्णांकerrupts off, so use
 * mdelay in that हाल.
 */
अटल sमाप_प्रकार opal_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	s64 rc = OPAL_BUSY;
	पूर्णांक off;

	अगर (*index >= nvram_size)
		वापस 0;
	off = *index;
	अगर ((off + count) > nvram_size)
		count = nvram_size - off;

	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_ग_लिखो_nvram(__pa(buf), count, off);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			अगर (in_पूर्णांकerrupt() || irqs_disabled())
				mdelay(OPAL_BUSY_DELAY_MS);
			अन्यथा
				msleep(OPAL_BUSY_DELAY_MS);
			opal_poll_events(शून्य);
		पूर्ण अन्यथा अगर (rc == OPAL_BUSY) अणु
			अगर (in_पूर्णांकerrupt() || irqs_disabled())
				mdelay(OPAL_BUSY_DELAY_MS);
			अन्यथा
				msleep(OPAL_BUSY_DELAY_MS);
		पूर्ण
	पूर्ण

	अगर (rc)
		वापस -EIO;

	*index += count;
	वापस count;
पूर्ण

अटल पूर्णांक __init opal_nvram_init_log_partitions(व्योम)
अणु
	/* Scan nvram क्रम partitions */
	nvram_scan_partitions();
	nvram_init_oops_partition(0);
	वापस 0;
पूर्ण
machine_arch_initcall(घातernv, opal_nvram_init_log_partitions);

व्योम __init opal_nvram_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *nbytes_p;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,opal-nvram");
	अगर (np == शून्य)
		वापस;

	nbytes_p = of_get_property(np, "#bytes", शून्य);
	अगर (!nbytes_p) अणु
		of_node_put(np);
		वापस;
	पूर्ण
	nvram_size = be32_to_cpup(nbytes_p);

	pr_info("OPAL nvram setup, %u bytes\n", nvram_size);
	of_node_put(np);

	ppc_md.nvram_पढ़ो = opal_nvram_पढ़ो;
	ppc_md.nvram_ग_लिखो = opal_nvram_ग_लिखो;
	ppc_md.nvram_size = opal_nvram_size;
पूर्ण

