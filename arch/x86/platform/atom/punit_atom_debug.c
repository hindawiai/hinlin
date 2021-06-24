<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel SOC Punit device state debug driver
 * Punit controls घातer management क्रम North Complex devices (Graphics
 * blocks, Image Signal Processing, video processing, display, DSP etc.)
 *
 * Copyright (c) 2015, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/iosf_mbi.h>

/* Subप्रणाली config/status Video processor */
#घोषणा VED_SS_PM0		0x32
/* Subप्रणाली config/status ISP (Image Signal Processor) */
#घोषणा ISP_SS_PM0		0x39
/* Subप्रणाली config/status Input/output controller */
#घोषणा MIO_SS_PM		0x3B
/* Shअगरt bits क्रम getting status क्रम video, isp and i/o */
#घोषणा SSS_SHIFT		24

/* Power gate status reg */
#घोषणा PWRGT_STATUS		0x61
/* Shअगरt bits क्रम getting status क्रम graphics rendering */
#घोषणा RENDER_POS		0
/* Shअगरt bits क्रम getting status क्रम media control */
#घोषणा MEDIA_POS		2
/* Shअगरt bits क्रम getting status क्रम Valley View/Baytrail display */
#घोषणा VLV_DISPLAY_POS		6

/* Subप्रणाली config/status display क्रम Cherry Trail SOC */
#घोषणा CHT_DSP_SSS		0x36
/* Shअगरt bits क्रम getting status क्रम display */
#घोषणा CHT_DSP_SSS_POS		16

काष्ठा punit_device अणु
	अक्षर *name;
	पूर्णांक reg;
	पूर्णांक sss_pos;
पूर्ण;

अटल स्थिर काष्ठा punit_device punit_device_tng[] = अणु
	अणु "DISPLAY",	CHT_DSP_SSS,	SSS_SHIFT पूर्ण,
	अणु "VED",	VED_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "ISP",	ISP_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "MIO",	MIO_SS_PM,	SSS_SHIFT पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा punit_device punit_device_byt[] = अणु
	अणु "GFX RENDER",	PWRGT_STATUS,	RENDER_POS पूर्ण,
	अणु "GFX MEDIA",	PWRGT_STATUS,	MEDIA_POS पूर्ण,
	अणु "DISPLAY",	PWRGT_STATUS,	VLV_DISPLAY_POS पूर्ण,
	अणु "VED",	VED_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "ISP",	ISP_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "MIO",	MIO_SS_PM,	SSS_SHIFT पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा punit_device punit_device_cht[] = अणु
	अणु "GFX RENDER",	PWRGT_STATUS,	RENDER_POS पूर्ण,
	अणु "GFX MEDIA",	PWRGT_STATUS,	MEDIA_POS पूर्ण,
	अणु "DISPLAY",	CHT_DSP_SSS,	CHT_DSP_SSS_POS पूर्ण,
	अणु "VED",	VED_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "ISP",	ISP_SS_PM0,	SSS_SHIFT पूर्ण,
	अणु "MIO",	MIO_SS_PM,	SSS_SHIFT पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर dstates[] = अणु"D0", "D0i1", "D0i2", "D0i3"पूर्ण;

अटल पूर्णांक punit_dev_state_show(काष्ठा seq_file *seq_file, व्योम *unused)
अणु
	u32 punit_pwr_status;
	काष्ठा punit_device *punit_devp = seq_file->निजी;
	पूर्णांक index;
	पूर्णांक status;

	seq_माला_दो(seq_file, "\n\nPUNIT NORTH COMPLEX DEVICES :\n");
	जबतक (punit_devp->name) अणु
		status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
				       punit_devp->reg, &punit_pwr_status);
		अगर (status) अणु
			seq_म_लिखो(seq_file, "%9s : Read Failed\n",
				   punit_devp->name);
		पूर्ण अन्यथा  अणु
			index = (punit_pwr_status >> punit_devp->sss_pos) & 3;
			seq_म_लिखो(seq_file, "%9s : %s\n", punit_devp->name,
				   dstates[index]);
		पूर्ण
		punit_devp++;
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(punit_dev_state);

अटल काष्ठा dentry *punit_dbg_file;

अटल व्योम punit_dbgfs_रेजिस्टर(काष्ठा punit_device *punit_device)
अणु
	punit_dbg_file = debugfs_create_dir("punit_atom", शून्य);

	debugfs_create_file("dev_power_state", 0444, punit_dbg_file,
			    punit_device, &punit_dev_state_fops);
पूर्ण

अटल व्योम punit_dbgfs_unरेजिस्टर(व्योम)
अणु
	debugfs_हटाओ_recursive(punit_dbg_file);
पूर्ण

#घोषणा X86_MATCH(model, data)						 \
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 6, INTEL_FAM6_##model, \
					   X86_FEATURE_MWAIT, data)

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_punit_cpu_ids[] = अणु
	X86_MATCH(ATOM_SILVERMONT,		&punit_device_byt),
	X86_MATCH(ATOM_SILVERMONT_MID,		&punit_device_tng),
	X86_MATCH(ATOM_AIRMONT,			&punit_device_cht),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_punit_cpu_ids);

अटल पूर्णांक __init punit_atom_debug_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;

	id = x86_match_cpu(पूर्णांकel_punit_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	punit_dbgfs_रेजिस्टर((काष्ठा punit_device *)id->driver_data);

	वापस 0;
पूर्ण

अटल व्योम __निकास punit_atom_debug_निकास(व्योम)
अणु
	punit_dbgfs_unरेजिस्टर();
पूर्ण

module_init(punit_atom_debug_init);
module_निकास(punit_atom_debug_निकास);

MODULE_AUTHOR("Kumar P, Mahesh <mahesh.kumar.p@intel.com>");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_DESCRIPTION("Driver for Punit devices states debugging");
MODULE_LICENSE("GPL v2");
