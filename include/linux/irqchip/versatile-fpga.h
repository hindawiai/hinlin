<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PLAT_FPGA_IRQ_H
#घोषणा PLAT_FPGA_IRQ_H

काष्ठा device_node;
काष्ठा pt_regs;

व्योम fpga_handle_irq(काष्ठा pt_regs *regs);
व्योम fpga_irq_init(व्योम __iomem *, स्थिर अक्षर *, पूर्णांक, पूर्णांक, u32,
		काष्ठा device_node *node);
पूर्णांक fpga_irq_of_init(काष्ठा device_node *node,
		     काष्ठा device_node *parent);

#पूर्ण_अगर
