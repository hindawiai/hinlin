<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/pci.h>
#समावेश "ops.h"

अटल
bool snd_sof_pci_update_bits_unlocked(काष्ठा snd_sof_dev *sdev, u32 offset,
				      u32 mask, u32 value)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	अचिन्हित पूर्णांक old, new;
	u32 ret = 0;

	pci_पढ़ो_config_dword(pci, offset, &ret);
	old = ret;
	dev_dbg(sdev->dev, "Debug PCIR: %8.8x at  %8.8x\n", old & mask, offset);

	new = (old & ~mask) | (value & mask);

	अगर (old == new)
		वापस false;

	pci_ग_लिखो_config_dword(pci, offset, new);
	dev_dbg(sdev->dev, "Debug PCIW: %8.8x at  %8.8x\n", value,
		offset);

	वापस true;
पूर्ण

bool snd_sof_pci_update_bits(काष्ठा snd_sof_dev *sdev, u32 offset,
			     u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	bool change;

	spin_lock_irqsave(&sdev->hw_lock, flags);
	change = snd_sof_pci_update_bits_unlocked(sdev, offset, mask, value);
	spin_unlock_irqrestore(&sdev->hw_lock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL(snd_sof_pci_update_bits);

bool snd_sof_dsp_update_bits_unlocked(काष्ठा snd_sof_dev *sdev, u32 bar,
				      u32 offset, u32 mask, u32 value)
अणु
	अचिन्हित पूर्णांक old, new;
	u32 ret;

	ret = snd_sof_dsp_पढ़ो(sdev, bar, offset);

	old = ret;
	new = (old & ~mask) | (value & mask);

	अगर (old == new)
		वापस false;

	snd_sof_dsp_ग_लिखो(sdev, bar, offset, new);

	वापस true;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_update_bits_unlocked);

bool snd_sof_dsp_update_bits64_unlocked(काष्ठा snd_sof_dev *sdev, u32 bar,
					u32 offset, u64 mask, u64 value)
अणु
	u64 old, new;

	old = snd_sof_dsp_पढ़ो64(sdev, bar, offset);

	new = (old & ~mask) | (value & mask);

	अगर (old == new)
		वापस false;

	snd_sof_dsp_ग_लिखो64(sdev, bar, offset, new);

	वापस true;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_update_bits64_unlocked);

/* This is क्रम रेजिस्टरs bits with attribute RWC */
bool snd_sof_dsp_update_bits(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset,
			     u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	bool change;

	spin_lock_irqsave(&sdev->hw_lock, flags);
	change = snd_sof_dsp_update_bits_unlocked(sdev, bar, offset, mask,
						  value);
	spin_unlock_irqrestore(&sdev->hw_lock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_update_bits);

bool snd_sof_dsp_update_bits64(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset,
			       u64 mask, u64 value)
अणु
	अचिन्हित दीर्घ flags;
	bool change;

	spin_lock_irqsave(&sdev->hw_lock, flags);
	change = snd_sof_dsp_update_bits64_unlocked(sdev, bar, offset, mask,
						    value);
	spin_unlock_irqrestore(&sdev->hw_lock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_update_bits64);

अटल
व्योम snd_sof_dsp_update_bits_क्रमced_unlocked(काष्ठा snd_sof_dev *sdev, u32 bar,
					     u32 offset, u32 mask, u32 value)
अणु
	अचिन्हित पूर्णांक old, new;
	u32 ret;

	ret = snd_sof_dsp_पढ़ो(sdev, bar, offset);

	old = ret;
	new = (old & ~mask) | (value & mask);

	snd_sof_dsp_ग_लिखो(sdev, bar, offset, new);
पूर्ण

/* This is क्रम रेजिस्टरs bits with attribute RWC */
व्योम snd_sof_dsp_update_bits_क्रमced(काष्ठा snd_sof_dev *sdev, u32 bar,
				    u32 offset, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdev->hw_lock, flags);
	snd_sof_dsp_update_bits_क्रमced_unlocked(sdev, bar, offset, mask, value);
	spin_unlock_irqrestore(&sdev->hw_lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_update_bits_क्रमced);

व्योम snd_sof_dsp_panic(काष्ठा snd_sof_dev *sdev, u32 offset)
अणु
	dev_err(sdev->dev, "error : DSP panic!\n");

	/*
	 * check अगर DSP is not पढ़ोy and did not set the dsp_oops_offset.
	 * अगर the dsp_oops_offset is not set, set it from the panic message.
	 * Also add a check to memory winकरोw setting with panic message.
	 */
	अगर (!sdev->dsp_oops_offset)
		sdev->dsp_oops_offset = offset;
	अन्यथा
		dev_dbg(sdev->dev, "panic: dsp_oops_offset %zu offset %d\n",
			sdev->dsp_oops_offset, offset);

	snd_sof_dsp_dbg_dump(sdev, SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_MBOX);
	snd_sof_trace_notअगरy_क्रम_error(sdev);
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_panic);
