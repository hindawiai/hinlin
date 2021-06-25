<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_OSDEP_H_
#घोषणा _IAVF_OSDEP_H_

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/tcp.h>
#समावेश <linux/pci.h>

/* get पढ़ोq/ग_लिखोq support क्रम 32 bit kernels, use the low-first version */
#समावेश <linux/io-64-nonatomic-lo-hi.h>

/* File to be the magic between shared code and
 * actual OS primitives
 */

#घोषणा hw_dbg(hw, S, A...)	करो अणुपूर्ण जबतक (0)

#घोषणा wr32(a, reg, value)	ग_लिखोl((value), ((a)->hw_addr + (reg)))
#घोषणा rd32(a, reg)		पढ़ोl((a)->hw_addr + (reg))

#घोषणा wr64(a, reg, value)	ग_लिखोq((value), ((a)->hw_addr + (reg)))
#घोषणा rd64(a, reg)		पढ़ोq((a)->hw_addr + (reg))
#घोषणा iavf_flush(a)		पढ़ोl((a)->hw_addr + IAVF_VFGEN_RSTAT)

/* memory allocation tracking */
काष्ठा iavf_dma_mem अणु
	व्योम *va;
	dma_addr_t pa;
	u32 size;
पूर्ण;

#घोषणा iavf_allocate_dma_mem(h, m, unused, s, a) \
	iavf_allocate_dma_mem_d(h, m, s, a)
#घोषणा iavf_मुक्त_dma_mem(h, m) iavf_मुक्त_dma_mem_d(h, m)

काष्ठा iavf_virt_mem अणु
	व्योम *va;
	u32 size;
पूर्ण;
#घोषणा iavf_allocate_virt_mem(h, m, s) iavf_allocate_virt_mem_d(h, m, s)
#घोषणा iavf_मुक्त_virt_mem(h, m) iavf_मुक्त_virt_mem_d(h, m)

#घोषणा iavf_debug(h, m, s, ...)				\
करो अणु								\
	अगर (((m) & (h)->debug_mask))				\
		pr_info("iavf %02x:%02x.%x " s,			\
			(h)->bus.bus_id, (h)->bus.device,	\
			(h)->bus.func, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _IAVF_OSDEP_H_ */
