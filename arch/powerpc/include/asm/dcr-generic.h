<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अगर_अघोषित _ASM_POWERPC_DCR_GENERIC_H
#घोषणा _ASM_POWERPC_DCR_GENERIC_H
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__

क्रमागत host_type_t अणुDCR_HOST_MMIO, DCR_HOST_NATIVE, DCR_HOST_INVALIDपूर्ण;

प्रकार काष्ठा अणु
	क्रमागत host_type_t type;
	जोड़ अणु
		dcr_host_mmio_t mmio;
		dcr_host_native_t native;
	पूर्ण host;
पूर्ण dcr_host_t;

बाह्य bool dcr_map_ok_generic(dcr_host_t host);

बाह्य dcr_host_t dcr_map_generic(काष्ठा device_node *dev, अचिन्हित पूर्णांक dcr_n,
			  अचिन्हित पूर्णांक dcr_c);
बाह्य व्योम dcr_unmap_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_c);

बाह्य u32 dcr_पढ़ो_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_n);

बाह्य व्योम dcr_ग_लिखो_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_n, u32 value);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_DCR_GENERIC_H */


