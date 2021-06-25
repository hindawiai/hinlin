<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 *  Copyright (C) 2013-2015 Lantiq Beteiligungs-GmbH & Co.KG
 */

#समावेश <linux/export.h>
#समावेश <linux/clk.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>

#समावेश <lantiq_soc.h>

#समावेश "../prom.h"

#घोषणा SOC_DANUBE	"Danube"
#घोषणा SOC_TWINPASS	"Twinpass"
#घोषणा SOC_AMAZON_SE	"Amazon_SE"
#घोषणा SOC_AR9		"AR9"
#घोषणा SOC_GR9		"GRX200"
#घोषणा SOC_VR9		"xRX200"
#घोषणा SOC_VRX220	"xRX220"
#घोषणा SOC_AR10	"xRX300"
#घोषणा SOC_GRX390	"xRX330"

#घोषणा COMP_DANUBE	"lantiq,danube"
#घोषणा COMP_TWINPASS	"lantiq,twinpass"
#घोषणा COMP_AMAZON_SE	"lantiq,ase"
#घोषणा COMP_AR9	"lantiq,ar9"
#घोषणा COMP_GR9	"lantiq,gr9"
#घोषणा COMP_VR9	"lantiq,vr9"
#घोषणा COMP_AR10	"lantiq,ar10"
#घोषणा COMP_GRX390	"lantiq,grx390"

#घोषणा PART_SHIFT	12
#घोषणा PART_MASK	0x0FFFFFFF
#घोषणा REV_SHIFT	28
#घोषणा REV_MASK	0xF0000000

व्योम __init ltq_soc_detect(काष्ठा ltq_soc_info *i)
अणु
	i->partnum = (ltq_r32(LTQ_MPS_CHIPID) & PART_MASK) >> PART_SHIFT;
	i->rev = (ltq_r32(LTQ_MPS_CHIPID) & REV_MASK) >> REV_SHIFT;
	प्र_लिखो(i->rev_type, "1.%d", i->rev);
	चयन (i->partnum) अणु
	हाल SOC_ID_DANUBE1:
	हाल SOC_ID_DANUBE2:
		i->name = SOC_DANUBE;
		i->type = SOC_TYPE_DANUBE;
		i->compatible = COMP_DANUBE;
		अवरोध;

	हाल SOC_ID_TWINPASS:
		i->name = SOC_TWINPASS;
		i->type = SOC_TYPE_DANUBE;
		i->compatible = COMP_TWINPASS;
		अवरोध;

	हाल SOC_ID_ARX188:
	हाल SOC_ID_ARX168_1:
	हाल SOC_ID_ARX168_2:
	हाल SOC_ID_ARX182:
		i->name = SOC_AR9;
		i->type = SOC_TYPE_AR9;
		i->compatible = COMP_AR9;
		अवरोध;

	हाल SOC_ID_GRX188:
	हाल SOC_ID_GRX168:
		i->name = SOC_GR9;
		i->type = SOC_TYPE_AR9;
		i->compatible = COMP_GR9;
		अवरोध;

	हाल SOC_ID_AMAZON_SE_1:
	हाल SOC_ID_AMAZON_SE_2:
#अगर_घोषित CONFIG_PCI
		panic("ase is only supported for non pci kernels");
#पूर्ण_अगर
		i->name = SOC_AMAZON_SE;
		i->type = SOC_TYPE_AMAZON_SE;
		i->compatible = COMP_AMAZON_SE;
		अवरोध;

	हाल SOC_ID_VRX282:
	हाल SOC_ID_VRX268:
	हाल SOC_ID_VRX288:
		i->name = SOC_VR9;
		i->type = SOC_TYPE_VR9;
		i->compatible = COMP_VR9;
		अवरोध;

	हाल SOC_ID_GRX268:
	हाल SOC_ID_GRX288:
		i->name = SOC_GR9;
		i->type = SOC_TYPE_VR9;
		i->compatible = COMP_GR9;
		अवरोध;

	हाल SOC_ID_VRX268_2:
	हाल SOC_ID_VRX288_2:
		i->name = SOC_VR9;
		i->type = SOC_TYPE_VR9_2;
		i->compatible = COMP_VR9;
		अवरोध;

	हाल SOC_ID_VRX220:
		i->name = SOC_VRX220;
		i->type = SOC_TYPE_VRX220;
		i->compatible = COMP_VR9;
		अवरोध;

	हाल SOC_ID_GRX282_2:
	हाल SOC_ID_GRX288_2:
		i->name = SOC_GR9;
		i->type = SOC_TYPE_VR9_2;
		i->compatible = COMP_GR9;
		अवरोध;

	हाल SOC_ID_ARX362:
	हाल SOC_ID_ARX368:
	हाल SOC_ID_ARX382:
	हाल SOC_ID_ARX388:
	हाल SOC_ID_URX388:
		i->name = SOC_AR10;
		i->type = SOC_TYPE_AR10;
		i->compatible = COMP_AR10;
		अवरोध;

	हाल SOC_ID_GRX383:
	हाल SOC_ID_GRX369:
	हाल SOC_ID_GRX387:
	हाल SOC_ID_GRX389:
		i->name = SOC_GRX390;
		i->type = SOC_TYPE_GRX390;
		i->compatible = COMP_GRX390;
		अवरोध;

	शेष:
		unreachable();
		अवरोध;
	पूर्ण
पूर्ण
