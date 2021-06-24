<शैली गुरु>
/*
 * Workbit NinjaSCSI-32Bi/UDE PCI/CardBus SCSI Host Bus Adapter driver
 * I/O routine
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License.
 */

#अगर_अघोषित _NSP32_IO_H
#घोषणा _NSP32_IO_H

अटल अंतरभूत व्योम nsp32_ग_लिखो1(अचिन्हित पूर्णांक  base,
				अचिन्हित पूर्णांक  index,
				अचिन्हित अक्षर val)
अणु
	outb(val, (base + index));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nsp32_पढ़ो1(अचिन्हित पूर्णांक base,
					अचिन्हित पूर्णांक index)
अणु
	वापस inb(base + index);
पूर्ण

अटल अंतरभूत व्योम nsp32_ग_लिखो2(अचिन्हित पूर्णांक   base,
				अचिन्हित पूर्णांक   index,
				अचिन्हित लघु val)
अणु
	outw(val, (base + index));
पूर्ण

अटल अंतरभूत अचिन्हित लघु nsp32_पढ़ो2(अचिन्हित पूर्णांक base,
					 अचिन्हित पूर्णांक index)
अणु
	वापस inw(base + index);
पूर्ण

अटल अंतरभूत व्योम nsp32_ग_लिखो4(अचिन्हित पूर्णांक  base,
				अचिन्हित पूर्णांक  index,
				अचिन्हित दीर्घ val)
अणु
	outl(val, (base + index));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nsp32_पढ़ो4(अचिन्हित पूर्णांक base,
					अचिन्हित पूर्णांक index)
अणु
	वापस inl(base + index);
पूर्ण

/*==============================================*/

अटल अंतरभूत व्योम nsp32_mmio_ग_लिखो1(अचिन्हित दीर्घ base,
				     अचिन्हित पूर्णांक  index,
				     अचिन्हित अक्षर val)
अणु
	अस्थिर अचिन्हित अक्षर *ptr;

	ptr = (अचिन्हित अक्षर *)(base + NSP32_MMIO_OFFSET + index);

	ग_लिखोb(val, ptr);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nsp32_mmio_पढ़ो1(अचिन्हित दीर्घ base,
					     अचिन्हित पूर्णांक  index)
अणु
	अस्थिर अचिन्हित अक्षर *ptr;

	ptr = (अचिन्हित अक्षर *)(base + NSP32_MMIO_OFFSET + index);

	वापस पढ़ोb(ptr);
पूर्ण

अटल अंतरभूत व्योम nsp32_mmio_ग_लिखो2(अचिन्हित दीर्घ  base,
				     अचिन्हित पूर्णांक   index,
				     अचिन्हित लघु val)
अणु
	अस्थिर अचिन्हित लघु *ptr;

	ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + index);

	ग_लिखोw(cpu_to_le16(val), ptr);
पूर्ण

अटल अंतरभूत अचिन्हित लघु nsp32_mmio_पढ़ो2(अचिन्हित दीर्घ base,
					      अचिन्हित पूर्णांक  index)
अणु
	अस्थिर अचिन्हित लघु *ptr;

	ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + index);

	वापस le16_to_cpu(पढ़ोw(ptr));
पूर्ण

अटल अंतरभूत व्योम nsp32_mmio_ग_लिखो4(अचिन्हित दीर्घ base,
				     अचिन्हित पूर्णांक  index,
				     अचिन्हित दीर्घ val)
अणु
	अस्थिर अचिन्हित दीर्घ *ptr;

	ptr = (अचिन्हित दीर्घ *)(base + NSP32_MMIO_OFFSET + index);

	ग_लिखोl(cpu_to_le32(val), ptr);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nsp32_mmio_पढ़ो4(अचिन्हित दीर्घ base,
					     अचिन्हित पूर्णांक  index)
अणु
	अस्थिर अचिन्हित दीर्घ *ptr;

	ptr = (अचिन्हित दीर्घ *)(base + NSP32_MMIO_OFFSET + index);

	वापस le32_to_cpu(पढ़ोl(ptr));
पूर्ण

/*==============================================*/

अटल अंतरभूत अचिन्हित अक्षर nsp32_index_पढ़ो1(अचिन्हित पूर्णांक base,
					      अचिन्हित पूर्णांक reg)
अणु
	outb(reg, base + INDEX_REG);
	वापस inb(base + DATA_REG_LOW);
पूर्ण

अटल अंतरभूत व्योम nsp32_index_ग_लिखो1(अचिन्हित पूर्णांक  base,
				      अचिन्हित पूर्णांक  reg,
				      अचिन्हित अक्षर val)
अणु
	outb(reg, base + INDEX_REG   );
	outb(val, base + DATA_REG_LOW);
पूर्ण

अटल अंतरभूत अचिन्हित लघु nsp32_index_पढ़ो2(अचिन्हित पूर्णांक base,
					       अचिन्हित पूर्णांक reg)
अणु
	outb(reg, base + INDEX_REG);
	वापस inw(base + DATA_REG_LOW);
पूर्ण

अटल अंतरभूत व्योम nsp32_index_ग_लिखो2(अचिन्हित पूर्णांक   base,
				      अचिन्हित पूर्णांक   reg,
				      अचिन्हित लघु val)
अणु
	outb(reg, base + INDEX_REG   );
	outw(val, base + DATA_REG_LOW);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nsp32_index_पढ़ो4(अचिन्हित पूर्णांक base,
					      अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ h,l;

	outb(reg, base + INDEX_REG);
	l = inw(base + DATA_REG_LOW);
	h = inw(base + DATA_REG_HI );

	वापस ((h << 16) | l);
पूर्ण

अटल अंतरभूत व्योम nsp32_index_ग_लिखो4(अचिन्हित पूर्णांक  base,
				      अचिन्हित पूर्णांक  reg,
				      अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ h,l;

	h = (val & 0xffff0000) >> 16;
	l = (val & 0x0000ffff) >>  0;

	outb(reg, base + INDEX_REG   );
	outw(l,   base + DATA_REG_LOW);
	outw(h,   base + DATA_REG_HI );
पूर्ण

/*==============================================*/

अटल अंतरभूत अचिन्हित अक्षर nsp32_mmio_index_पढ़ो1(अचिन्हित दीर्घ base,
						   अचिन्हित पूर्णांक reg)
अणु
	अस्थिर अचिन्हित लघु *index_ptr, *data_ptr;

	index_ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + INDEX_REG);
	data_ptr  = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + DATA_REG_LOW);

	ग_लिखोb(reg, index_ptr);
	वापस पढ़ोb(data_ptr);
पूर्ण

अटल अंतरभूत व्योम nsp32_mmio_index_ग_लिखो1(अचिन्हित दीर्घ base,
					   अचिन्हित पूर्णांक  reg,
					   अचिन्हित अक्षर val)
अणु
	अस्थिर अचिन्हित लघु *index_ptr, *data_ptr;

	index_ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + INDEX_REG);
	data_ptr  = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + DATA_REG_LOW);

	ग_लिखोb(reg, index_ptr);
	ग_लिखोb(val, data_ptr );
पूर्ण

अटल अंतरभूत अचिन्हित लघु nsp32_mmio_index_पढ़ो2(अचिन्हित दीर्घ base,
						    अचिन्हित पूर्णांक  reg)
अणु
	अस्थिर अचिन्हित लघु *index_ptr, *data_ptr;

	index_ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + INDEX_REG);
	data_ptr  = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + DATA_REG_LOW);

	ग_लिखोb(reg, index_ptr);
	वापस le16_to_cpu(पढ़ोw(data_ptr));
पूर्ण

अटल अंतरभूत व्योम nsp32_mmio_index_ग_लिखो2(अचिन्हित दीर्घ  base,
					   अचिन्हित पूर्णांक   reg,
					   अचिन्हित लघु val)
अणु
	अस्थिर अचिन्हित लघु *index_ptr, *data_ptr;

	index_ptr = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + INDEX_REG);
	data_ptr  = (अचिन्हित लघु *)(base + NSP32_MMIO_OFFSET + DATA_REG_LOW);

	ग_लिखोb(reg,              index_ptr);
	ग_लिखोw(cpu_to_le16(val), data_ptr );
पूर्ण

/*==============================================*/

अटल अंतरभूत व्योम nsp32_multi_पढ़ो4(अचिन्हित पूर्णांक   base,
				     अचिन्हित पूर्णांक   reg,
				     व्योम          *buf,
				     अचिन्हित दीर्घ  count)
अणु
	insl(base + reg, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp32_fअगरo_पढ़ो(अचिन्हित पूर्णांक   base,
				   व्योम          *buf,
				   अचिन्हित दीर्घ  count)
अणु
	nsp32_multi_पढ़ो4(base, FIFO_DATA_LOW, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp32_multi_ग_लिखो4(अचिन्हित पूर्णांक   base,
				      अचिन्हित पूर्णांक   reg,
				      व्योम          *buf,
				      अचिन्हित दीर्घ  count)
अणु
	outsl(base + reg, buf, count);
पूर्ण

अटल अंतरभूत व्योम nsp32_fअगरo_ग_लिखो(अचिन्हित पूर्णांक   base,
				    व्योम          *buf,
				    अचिन्हित दीर्घ  count)
अणु
	nsp32_multi_ग_लिखो4(base, FIFO_DATA_LOW, buf, count);
पूर्ण

#पूर्ण_अगर /* _NSP32_IO_H */
/* end */
