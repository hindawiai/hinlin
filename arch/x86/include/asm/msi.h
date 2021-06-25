<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MSI_H
#घोषणा _ASM_X86_MSI_H
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/irqकरोमुख्य.h>

प्रकार काष्ठा irq_alloc_info msi_alloc_info_t;

पूर्णांक pci_msi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev, पूर्णांक nvec,
		    msi_alloc_info_t *arg);

/* Structs and defines क्रम the X86 specअगरic MSI message क्रमmat */

प्रकार काष्ठा x86_msi_data अणु
	u32	vector			:  8,
		delivery_mode		:  3,
		dest_mode_logical	:  1,
		reserved		:  2,
		active_low		:  1,
		is_level		:  1;

	u32	dmar_subhandle;
पूर्ण __attribute__ ((packed)) arch_msi_msg_data_t;
#घोषणा arch_msi_msg_data	x86_msi_data

प्रकार काष्ठा x86_msi_addr_lo अणु
	जोड़ अणु
		काष्ठा अणु
			u32	reserved_0		:  2,
				dest_mode_logical	:  1,
				redirect_hपूर्णांक		:  1,
				reserved_1		:  1,
				virt_destid_8_14	:  7,
				destid_0_7		:  8,
				base_address		: 12;
		पूर्ण;
		काष्ठा अणु
			u32	dmar_reserved_0		:  2,
				dmar_index_15		:  1,
				dmar_subhandle_valid	:  1,
				dmar_क्रमmat		:  1,
				dmar_index_0_14		: 15,
				dmar_base_address	: 12;
		पूर्ण;
	पूर्ण;
पूर्ण __attribute__ ((packed)) arch_msi_msg_addr_lo_t;
#घोषणा arch_msi_msg_addr_lo	x86_msi_addr_lo

#घोषणा X86_MSI_BASE_ADDRESS_LOW	(0xfee00000 >> 20)

प्रकार काष्ठा x86_msi_addr_hi अणु
	u32	reserved		:  8,
		destid_8_31		: 24;
पूर्ण __attribute__ ((packed)) arch_msi_msg_addr_hi_t;
#घोषणा arch_msi_msg_addr_hi	x86_msi_addr_hi

#घोषणा X86_MSI_BASE_ADDRESS_HIGH	(0)

काष्ठा msi_msg;
u32 x86_msi_msg_get_destid(काष्ठा msi_msg *msg, bool extid);

#पूर्ण_अगर /* _ASM_X86_MSI_H */
