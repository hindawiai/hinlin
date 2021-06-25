<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अगर_अघोषित _ASM_POWERPC_DCR_H
#घोषणा _ASM_POWERPC_DCR_H
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_PPC_DCR

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
#समावेश <यंत्र/dcr-native.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_DCR_MMIO
#समावेश <यंत्र/dcr-mmपन.स>
#पूर्ण_अगर


/* Indirection layer क्रम providing both NATIVE and MMIO support. */

#अगर defined(CONFIG_PPC_DCR_NATIVE) && defined(CONFIG_PPC_DCR_MMIO)

#समावेश <यंत्र/dcr-generic.h>

#घोषणा DCR_MAP_OK(host)	dcr_map_ok_generic(host)
#घोषणा dcr_map(dev, dcr_n, dcr_c) dcr_map_generic(dev, dcr_n, dcr_c)
#घोषणा dcr_unmap(host, dcr_c) dcr_unmap_generic(host, dcr_c)
#घोषणा dcr_पढ़ो(host, dcr_n) dcr_पढ़ो_generic(host, dcr_n)
#घोषणा dcr_ग_लिखो(host, dcr_n, value) dcr_ग_लिखो_generic(host, dcr_n, value)

#अन्यथा

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
प्रकार dcr_host_native_t dcr_host_t;
#घोषणा DCR_MAP_OK(host)	dcr_map_ok_native(host)
#घोषणा dcr_map(dev, dcr_n, dcr_c) dcr_map_native(dev, dcr_n, dcr_c)
#घोषणा dcr_unmap(host, dcr_c) dcr_unmap_native(host, dcr_c)
#घोषणा dcr_पढ़ो(host, dcr_n) dcr_पढ़ो_native(host, dcr_n)
#घोषणा dcr_ग_लिखो(host, dcr_n, value) dcr_ग_लिखो_native(host, dcr_n, value)
#अन्यथा
प्रकार dcr_host_mmio_t dcr_host_t;
#घोषणा DCR_MAP_OK(host)	dcr_map_ok_mmio(host)
#घोषणा dcr_map(dev, dcr_n, dcr_c) dcr_map_mmio(dev, dcr_n, dcr_c)
#घोषणा dcr_unmap(host, dcr_c) dcr_unmap_mmio(host, dcr_c)
#घोषणा dcr_पढ़ो(host, dcr_n) dcr_पढ़ो_mmio(host, dcr_n)
#घोषणा dcr_ग_लिखो(host, dcr_n, value) dcr_ग_लिखो_mmio(host, dcr_n, value)
#पूर्ण_अगर

#पूर्ण_अगर /* defined(CONFIG_PPC_DCR_NATIVE) && defined(CONFIG_PPC_DCR_MMIO) */

/*
 * additional helpers to पढ़ो the DCR * base from the device-tree
 */
काष्ठा device_node;
बाह्य अचिन्हित पूर्णांक dcr_resource_start(स्थिर काष्ठा device_node *np,
				       अचिन्हित पूर्णांक index);
बाह्य अचिन्हित पूर्णांक dcr_resource_len(स्थिर काष्ठा device_node *np,
				     अचिन्हित पूर्णांक index);
#पूर्ण_अगर /* CONFIG_PPC_DCR */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_DCR_H */
