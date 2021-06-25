<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Register Offsets क्रम Tegra194
 *
 * Copyright (c) 2018 NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_HOST1X07_HARDWARE_H
#घोषणा __HOST1X_HOST1X07_HARDWARE_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#समावेश "hw_host1x07_channel.h"
#समावेश "hw_host1x07_uclass.h"
#समावेश "hw_host1x07_vm.h"
#समावेश "hw_host1x07_hypervisor.h"

अटल अंतरभूत u32 host1x_class_host_रुको_syncpt(
	अचिन्हित indx, अचिन्हित threshold)
अणु
	वापस host1x_uclass_रुको_syncpt_indx_f(indx)
		| host1x_uclass_रुको_syncpt_thresh_f(threshold);
पूर्ण

अटल अंतरभूत u32 host1x_class_host_load_syncpt_base(
	अचिन्हित indx, अचिन्हित threshold)
अणु
	वापस host1x_uclass_load_syncpt_base_base_indx_f(indx)
		| host1x_uclass_load_syncpt_base_value_f(threshold);
पूर्ण

अटल अंतरभूत u32 host1x_class_host_रुको_syncpt_base(
	अचिन्हित indx, अचिन्हित base_indx, अचिन्हित offset)
अणु
	वापस host1x_uclass_रुको_syncpt_base_indx_f(indx)
		| host1x_uclass_रुको_syncpt_base_base_indx_f(base_indx)
		| host1x_uclass_रुको_syncpt_base_offset_f(offset);
पूर्ण

अटल अंतरभूत u32 host1x_class_host_incr_syncpt_base(
	अचिन्हित base_indx, अचिन्हित offset)
अणु
	वापस host1x_uclass_incr_syncpt_base_base_indx_f(base_indx)
		| host1x_uclass_incr_syncpt_base_offset_f(offset);
पूर्ण

अटल अंतरभूत u32 host1x_class_host_incr_syncpt(
	अचिन्हित cond, अचिन्हित indx)
अणु
	वापस host1x_uclass_incr_syncpt_cond_f(cond)
		| host1x_uclass_incr_syncpt_indx_f(indx);
पूर्ण

अटल अंतरभूत u32 host1x_class_host_inकरोff_reg_ग_लिखो(
	अचिन्हित mod_id, अचिन्हित offset, bool स्वतः_inc)
अणु
	u32 v = host1x_uclass_inकरोff_indbe_f(0xf)
		| host1x_uclass_inकरोff_indmodid_f(mod_id)
		| host1x_uclass_inकरोff_indroffset_f(offset);
	अगर (स्वतः_inc)
		v |= host1x_uclass_inकरोff_स्वतःinc_f(1);
	वापस v;
पूर्ण

अटल अंतरभूत u32 host1x_class_host_inकरोff_reg_पढ़ो(
	अचिन्हित mod_id, अचिन्हित offset, bool स्वतः_inc)
अणु
	u32 v = host1x_uclass_inकरोff_indmodid_f(mod_id)
		| host1x_uclass_inकरोff_indroffset_f(offset)
		| host1x_uclass_inकरोff_rwn_पढ़ो_v();
	अगर (स्वतः_inc)
		v |= host1x_uclass_inकरोff_स्वतःinc_f(1);
	वापस v;
पूर्ण

/* cdma opcodes */
अटल अंतरभूत u32 host1x_opcode_setclass(
	अचिन्हित class_id, अचिन्हित offset, अचिन्हित mask)
अणु
	वापस (0 << 28) | (offset << 16) | (class_id << 6) | mask;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_incr(अचिन्हित offset, अचिन्हित count)
अणु
	वापस (1 << 28) | (offset << 16) | count;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_nonincr(अचिन्हित offset, अचिन्हित count)
अणु
	वापस (2 << 28) | (offset << 16) | count;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_mask(अचिन्हित offset, अचिन्हित mask)
अणु
	वापस (3 << 28) | (offset << 16) | mask;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_imm(अचिन्हित offset, अचिन्हित value)
अणु
	वापस (4 << 28) | (offset << 16) | value;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_imm_incr_syncpt(अचिन्हित cond, अचिन्हित indx)
अणु
	वापस host1x_opcode_imm(host1x_uclass_incr_syncpt_r(),
		host1x_class_host_incr_syncpt(cond, indx));
पूर्ण

अटल अंतरभूत u32 host1x_opcode_restart(अचिन्हित address)
अणु
	वापस (5 << 28) | (address >> 4);
पूर्ण

अटल अंतरभूत u32 host1x_opcode_gather(अचिन्हित count)
अणु
	वापस (6 << 28) | count;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_gather_nonincr(अचिन्हित offset,	अचिन्हित count)
अणु
	वापस (6 << 28) | (offset << 16) | BIT(15) | count;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_gather_incr(अचिन्हित offset, अचिन्हित count)
अणु
	वापस (6 << 28) | (offset << 16) | BIT(15) | BIT(14) | count;
पूर्ण

अटल अंतरभूत u32 host1x_opcode_gather_wide(अचिन्हित count)
अणु
	वापस (12 << 28) | count;
पूर्ण

#घोषणा HOST1X_OPCODE_NOP host1x_opcode_nonincr(0, 0)

#पूर्ण_अगर
