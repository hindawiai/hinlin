<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LOONGSON_SMP_H_
#घोषणा __LOONGSON_SMP_H_

/* क्रम Loongson-3 smp support */
बाह्य अचिन्हित दीर्घ दीर्घ smp_group[4];

/* 4 groups(nodes) in maximum in numa हाल */
#घोषणा SMP_CORE_GROUP0_BASE	(smp_group[0])
#घोषणा SMP_CORE_GROUP1_BASE	(smp_group[1])
#घोषणा SMP_CORE_GROUP2_BASE	(smp_group[2])
#घोषणा SMP_CORE_GROUP3_BASE	(smp_group[3])

/* 4 cores in each group(node) */
#घोषणा SMP_CORE0_OFFSET  0x000
#घोषणा SMP_CORE1_OFFSET  0x100
#घोषणा SMP_CORE2_OFFSET  0x200
#घोषणा SMP_CORE3_OFFSET  0x300

/* ipi रेजिस्टरs offsets */
#घोषणा STATUS0  0x00
#घोषणा EN0      0x04
#घोषणा SET0     0x08
#घोषणा CLEAR0   0x0c
#घोषणा STATUS1  0x10
#घोषणा MASK1    0x14
#घोषणा SET1     0x18
#घोषणा CLEAR1   0x1c
#घोषणा BUF      0x20

#पूर्ण_अगर
