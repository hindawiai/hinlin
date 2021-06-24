<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अगर_अघोषित _ASM_POWERPC_DCR_MMIO_H
#घोषणा _ASM_POWERPC_DCR_MMIO_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/पन.स>

प्रकार काष्ठा अणु
	व्योम __iomem *token;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक base;
पूर्ण dcr_host_mmio_t;

अटल अंतरभूत bool dcr_map_ok_mmio(dcr_host_mmio_t host)
अणु
	वापस host.token != शून्य;
पूर्ण

बाह्य dcr_host_mmio_t dcr_map_mmio(काष्ठा device_node *dev,
				    अचिन्हित पूर्णांक dcr_n,
				    अचिन्हित पूर्णांक dcr_c);
बाह्य व्योम dcr_unmap_mmio(dcr_host_mmio_t host, अचिन्हित पूर्णांक dcr_c);

अटल अंतरभूत u32 dcr_पढ़ो_mmio(dcr_host_mmio_t host, अचिन्हित पूर्णांक dcr_n)
अणु
	वापस in_be32(host.token + ((host.base + dcr_n) * host.stride));
पूर्ण

अटल अंतरभूत व्योम dcr_ग_लिखो_mmio(dcr_host_mmio_t host,
				  अचिन्हित पूर्णांक dcr_n,
				  u32 value)
अणु
	out_be32(host.token + ((host.base + dcr_n) * host.stride), value);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_DCR_MMIO_H */


