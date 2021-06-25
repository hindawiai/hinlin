<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DAWR infraकाष्ठाure
 *
 * Copyright 2019, Michael Neuling, IBM Corporation.
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/hvcall.h>

bool dawr_क्रमce_enable;
EXPORT_SYMBOL_GPL(dawr_क्रमce_enable);

पूर्णांक set_dawr(पूर्णांक nr, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk)
अणु
	अचिन्हित दीर्घ dawr, dawrx, mrd;

	dawr = brk->address;

	dawrx  = (brk->type & (HW_BRK_TYPE_READ | HW_BRK_TYPE_WRITE))
		<< (63 - 58);
	dawrx |= ((brk->type & (HW_BRK_TYPE_TRANSLATE)) >> 2) << (63 - 59);
	dawrx |= (brk->type & (HW_BRK_TYPE_PRIV_ALL)) >> 3;
	/*
	 * DAWR length is stored in field MDR bits 48:53.  Matches range in
	 * द्विगुनwords (64 bits) baised by -1 eg. 0b000000=1DW and
	 * 0b111111=64DW.
	 * brk->hw_len is in bytes.
	 * This aligns up to द्विगुन word size, shअगरts and करोes the bias.
	 */
	mrd = ((brk->hw_len + 7) >> 3) - 1;
	dawrx |= (mrd & 0x3f) << (63 - 53);

	अगर (ppc_md.set_dawr)
		वापस ppc_md.set_dawr(nr, dawr, dawrx);

	अगर (nr == 0) अणु
		mtspr(SPRN_DAWR0, dawr);
		mtspr(SPRN_DAWRX0, dawrx);
	पूर्ण अन्यथा अणु
		mtspr(SPRN_DAWR1, dawr);
		mtspr(SPRN_DAWRX1, dawrx);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम disable_dawrs_cb(व्योम *info)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++)
		set_dawr(i, &null_brk);
पूर्ण

अटल sमाप_प्रकार dawr_ग_लिखो_file_bool(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;
	माप_प्रकार rc;

	/* Send error to user अगर they hypervisor won't allow us to ग_लिखो DAWR */
	अगर (!dawr_क्रमce_enable &&
	    firmware_has_feature(FW_FEATURE_LPAR) &&
	    set_dawr(0, &null_brk) != H_SUCCESS)
		वापस -ENODEV;

	rc = debugfs_ग_लिखो_file_bool(file, user_buf, count, ppos);
	अगर (rc)
		वापस rc;

	/* If we are clearing, make sure all CPUs have the DAWR cleared */
	अगर (!dawr_क्रमce_enable)
		smp_call_function(disable_dawrs_cb, शून्य, 0);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations dawr_enable_fops = अणु
	.पढ़ो =		debugfs_पढ़ो_file_bool,
	.ग_लिखो =	dawr_ग_लिखो_file_bool,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल पूर्णांक __init dawr_क्रमce_setup(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_DAWR)) अणु
		/* Don't setup sysfs file क्रम user control on P8 */
		dawr_क्रमce_enable = true;
		वापस 0;
	पूर्ण

	अगर (PVR_VER(mfspr(SPRN_PVR)) == PVR_POWER9) अणु
		/* Turn DAWR off by शेष, but allow admin to turn it on */
		debugfs_create_file_unsafe("dawr_enable_dangerous", 0600,
					   घातerpc_debugfs_root,
					   &dawr_क्रमce_enable,
					   &dawr_enable_fops);
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(dawr_क्रमce_setup);
