<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eisa_क्रमागतerator.c - provide support क्रम EISA adapters in PA-RISC machines
 *
 * Copyright (c) 2002 Daniel Engstrom <5116@telia.com>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <यंत्र/eisa_bus.h>
#समावेश <यंत्र/eisa_eeprom.h>


/*
 * Toकरो:
 * 
 * PORT init with MASK attr and other size than byte
 * MEMORY with other decode than 20 bit
 * CRC stuff
 * FREEFORM stuff
 */

#घोषणा EPI 0xc80
#घोषणा NUM_SLOT 16
#घोषणा SLOT2PORT(x) (x<<12)


/* macros to handle unaligned accesses and 
 * byte swapping. The data in the EEPROM is
 * little-endian on the big-endian PAROSC */
#घोषणा get_8(x) (*(u_पूर्णांक8_t*)(x))

अटल अंतरभूत u_पूर्णांक16_t get_16(स्थिर अचिन्हित अक्षर *x)
अणु 
	वापस (x[1] << 8) | x[0];
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t get_32(स्थिर अचिन्हित अक्षर *x)
अणु
	वापस (x[3] << 24) | (x[2] << 16) | (x[1] << 8) | x[0];
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t get_24(स्थिर अचिन्हित अक्षर *x)
अणु
	वापस (x[2] << 24) | (x[1] << 16) | (x[0] << 8);
पूर्ण

अटल व्योम prपूर्णांक_eisa_id(अक्षर *s, u_पूर्णांक32_t id)
अणु
	अक्षर venकरोr[4];
	पूर्णांक rev;
	पूर्णांक device;
	
	rev = id & 0xff;
	id >>= 8;
	device = id & 0xff;
	id >>= 8;
	venकरोr[3] = '\0';
	venकरोr[2] = '@' + (id & 0x1f);
	id >>= 5;	
	venकरोr[1] = '@' + (id & 0x1f);
	id >>= 5;	
	venकरोr[0] = '@' + (id & 0x1f);
	id >>= 5;	
	
	प्र_लिखो(s, "%s%02X%02X", venकरोr, device, rev);
पूर्ण
       
अटल पूर्णांक configure_memory(स्थिर अचिन्हित अक्षर *buf, 
		       काष्ठा resource *mem_parent,
		       अक्षर *name)
अणु
	पूर्णांक len;
	u_पूर्णांक8_t c;
	पूर्णांक i;
	काष्ठा resource *res;
	
	len=0;
	
	क्रम (i=0;i<HPEE_MEMORY_MAX_ENT;i++) अणु
		c = get_8(buf+len);
		
		अगर (शून्य != (res = kzalloc(माप(काष्ठा resource), GFP_KERNEL))) अणु
			पूर्णांक result;
			
			res->name = name;
			res->start = mem_parent->start + get_24(buf+len+2);
			res->end = res->start + get_16(buf+len+5)*1024;
			res->flags = IORESOURCE_MEM;
			pr_cont("memory %pR ", res);
			result = request_resource(mem_parent, res);
			अगर (result < 0) अणु
				prपूर्णांकk(KERN_ERR "EISA Enumerator: failed to claim EISA Bus address space!\n");
				वापस result;
			पूर्ण
		पूर्ण
		 	
		len+=7;      
	
		अगर (!(c & HPEE_MEMORY_MORE)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस len;
पूर्ण


अटल पूर्णांक configure_irq(स्थिर अचिन्हित अक्षर *buf)
अणु
	पूर्णांक len;
	u_पूर्णांक8_t c;
	पूर्णांक i;
	
	len=0;
	
	क्रम (i=0;i<HPEE_IRQ_MAX_ENT;i++) अणु
		c = get_8(buf+len);
		
		pr_cont("IRQ %d ", c & HPEE_IRQ_CHANNEL_MASK);
		अगर (c & HPEE_IRQ_TRIG_LEVEL) अणु
			eisa_make_irq_level(c & HPEE_IRQ_CHANNEL_MASK);
		पूर्ण अन्यथा अणु
			eisa_make_irq_edge(c & HPEE_IRQ_CHANNEL_MASK);
		पूर्ण
		
		len+=2; 
		/* hpux seems to allow क्रम
		 * two bytes of irq data but only defines one of
		 * them, I think */
		अगर  (!(c & HPEE_IRQ_MORE)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस len;
पूर्ण


अटल पूर्णांक configure_dma(स्थिर अचिन्हित अक्षर *buf)
अणु
	पूर्णांक len;
	u_पूर्णांक8_t c;
	पूर्णांक i;
	
	len=0;
	
	क्रम (i=0;i<HPEE_DMA_MAX_ENT;i++) अणु
		c = get_8(buf+len);
		pr_cont("DMA %d ", c&HPEE_DMA_CHANNEL_MASK);
		/* fixme: maybe initialize the dma channel withthe timing ? */
		len+=2;      
		अगर (!(c & HPEE_DMA_MORE)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस len;
पूर्ण

अटल पूर्णांक configure_port(स्थिर अचिन्हित अक्षर *buf, काष्ठा resource *io_parent,
		     अक्षर *board)
अणु
	पूर्णांक len;
	u_पूर्णांक8_t c;
	पूर्णांक i;
	काष्ठा resource *res;
	पूर्णांक result;
	
	len=0;
	
	क्रम (i=0;i<HPEE_PORT_MAX_ENT;i++) अणु
		c = get_8(buf+len);
		
		अगर (शून्य != (res = kzalloc(माप(काष्ठा resource), GFP_KERNEL))) अणु
			res->name = board;
			res->start = get_16(buf+len+1);
			res->end = get_16(buf+len+1)+(c&HPEE_PORT_SIZE_MASK)+1;
			res->flags = IORESOURCE_IO;
			pr_cont("ioports %pR ", res);
			result = request_resource(io_parent, res);
			अगर (result < 0) अणु
				prपूर्णांकk(KERN_ERR "EISA Enumerator: failed to claim EISA Bus address space!\n");
				वापस result;
			पूर्ण
		पूर्ण

		len+=3;      
		अगर (!(c & HPEE_PORT_MORE)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस len;
पूर्ण


/* byte 1 and 2 is the port number to ग_लिखो
 * and at byte 3 the value to ग_लिखो starts.
 * I assume that there are and- and or- masks
 * here when HPEE_PORT_INIT_MASK is set but I have 
 * not yet encountered this. */
अटल पूर्णांक configure_port_init(स्थिर अचिन्हित अक्षर *buf)
अणु
	पूर्णांक len=0;
	u_पूर्णांक8_t c;
	
	जबतक (len<HPEE_PORT_INIT_MAX_LEN) अणु
		पूर्णांक s=0;
		c = get_8(buf+len);
		
		चयन (c & HPEE_PORT_INIT_WIDTH_MASK)  अणु
		 हाल HPEE_PORT_INIT_WIDTH_BYTE:
			s=1;
			अगर (c & HPEE_PORT_INIT_MASK) अणु
				prपूर्णांकk(KERN_WARNING "port_init: unverified mask attribute\n");
				outb((inb(get_16(buf+len+1) & 
					  get_8(buf+len+3)) | 
				      get_8(buf+len+4)), get_16(buf+len+1));
				      
			पूर्ण अन्यथा अणु
				outb(get_8(buf+len+3), get_16(buf+len+1));
				      
			पूर्ण
			अवरोध;
		 हाल HPEE_PORT_INIT_WIDTH_WORD:
			s=2;
			अगर (c & HPEE_PORT_INIT_MASK) अणु
 				prपूर्णांकk(KERN_WARNING "port_init: unverified mask attribute\n");
				       outw((inw(get_16(buf+len+1)) &
					     get_16(buf+len+3)) |
					    get_16(buf+len+5), 
					    get_16(buf+len+1));
			पूर्ण अन्यथा अणु
				outw(cpu_to_le16(get_16(buf+len+3)), get_16(buf+len+1));
			पूर्ण
			अवरोध;
		 हाल HPEE_PORT_INIT_WIDTH_DWORD:
			s=4;
			अगर (c & HPEE_PORT_INIT_MASK) अणु
 				prपूर्णांकk(KERN_WARNING "port_init: unverified mask attribute\n");
				outl((inl(get_16(buf+len+1) &
					  get_32(buf+len+3)) |
				      get_32(buf+len+7)), get_16(buf+len+1));
			पूर्ण अन्यथा अणु
				outl(cpu_to_le32(get_32(buf+len+3)), get_16(buf+len+1));
			पूर्ण

			अवरोध;
		 शेष:
			prपूर्णांकk(KERN_ERR "Invalid port init word %02x\n", c);
			वापस 0;
		पूर्ण
		
		अगर (c & HPEE_PORT_INIT_MASK) अणु   
			s*=2;
		पूर्ण
		
		len+=s+3;
		अगर (!(c & HPEE_PORT_INIT_MORE)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	
	वापस len;
पूर्ण

अटल पूर्णांक configure_choise(स्थिर अचिन्हित अक्षर *buf, u_पूर्णांक8_t *info)
अणु
	पूर्णांक len;
	
	/* theis record contain the value of the functions
	 * configuration choises and an info byte which 
	 * describes which other records to expect in this 
	 * function */
	len = get_8(buf);
	*info=get_8(buf+len+1);
	 
	वापस len+2;
पूर्ण

अटल पूर्णांक configure_type_string(स्थिर अचिन्हित अक्षर *buf) 
अणु
	पूर्णांक len;
	
	/* just skip past the type field */
	len = get_8(buf);
	अगर (len > 80) अणु
		prपूर्णांकk(KERN_ERR "eisa_enumerator: type info field too long (%d, max is 80)\n", len);
	पूर्ण
	
	वापस 1+len;
पूर्ण

अटल पूर्णांक configure_function(स्थिर अचिन्हित अक्षर *buf, पूर्णांक *more) 
अणु
	/* the init field seems to be a two-byte field
	 * which is non-zero अगर there are an other function following
	 * I think it is the length of the function def 
	 */
	*more = get_16(buf);
	
	वापस 2;
पूर्ण

अटल पूर्णांक parse_slot_config(पूर्णांक slot,
			     स्थिर अचिन्हित अक्षर *buf,
			     काष्ठा eeprom_eisa_slot_info *es, 
			     काष्ठा resource *io_parent,
			     काष्ठा resource *mem_parent)
अणु
	पूर्णांक res=0;
	पूर्णांक function_len;
	अचिन्हित पूर्णांक pos=0;
	अचिन्हित पूर्णांक maxlen;
	पूर्णांक num_func=0;
	u_पूर्णांक8_t flags;
	पूर्णांक p0;
	
	अक्षर *board;
	पूर्णांक id_string_used=0;
	
	अगर (शून्य == (board = kदो_स्मृति(8, GFP_KERNEL))) अणु
		वापस -1;
	पूर्ण
	prपूर्णांक_eisa_id(board, es->eisa_slot_id);
	prपूर्णांकk(KERN_INFO "EISA slot %d: %s %s ", 
	       slot, board, es->flags&HPEE_FLAG_BOARD_IS_ISA ? "ISA" : "EISA");
	
	maxlen = es->config_data_length < HPEE_MAX_LENGTH ?
			 es->config_data_length : HPEE_MAX_LENGTH;
	जबतक ((pos < maxlen) && (num_func <= es->num_functions)) अणु
		pos+=configure_function(buf+pos, &function_len); 
		
		अगर (!function_len) अणु
			अवरोध;
		पूर्ण
		num_func++;
		p0 = pos;
		pos += configure_choise(buf+pos, &flags);

		अगर (flags & HPEE_FUNCTION_INFO_F_DISABLED) अणु
			/* function disabled, skip silently */
			pos = p0 + function_len;
			जारी;
		पूर्ण
		अगर (flags & HPEE_FUNCTION_INFO_CFG_FREE_FORM) अणु
			/* I have no idea how to handle this */
			prपूर्णांकk("function %d have free-form configuration, skipping ",
				num_func);
			pos = p0 + function_len;
			जारी;
		पूर्ण

		/* the ordering of the sections need
		 * more investigation.
		 * Currently I think that memory comaed beक्रमe IRQ
		 * I assume the order is LSB to MSB in the 
		 * info flags 
		 * eg type, memory, irq, dma, port, HPEE_PORT_init 
		 */

		अगर (flags & HPEE_FUNCTION_INFO_HAVE_TYPE) अणु
			pos += configure_type_string(buf+pos);
		पूर्ण
		
		अगर (flags & HPEE_FUNCTION_INFO_HAVE_MEMORY) अणु
			id_string_used=1;
			pos += configure_memory(buf+pos, mem_parent, board);
		पूर्ण 
		
		अगर (flags & HPEE_FUNCTION_INFO_HAVE_IRQ) अणु
			pos += configure_irq(buf+pos);
		पूर्ण 
		
		अगर (flags & HPEE_FUNCTION_INFO_HAVE_DMA) अणु
			pos += configure_dma(buf+pos);
		पूर्ण 
		
		अगर (flags & HPEE_FUNCTION_INFO_HAVE_PORT) अणु
			id_string_used=1;
			pos += configure_port(buf+pos, io_parent, board);
		पूर्ण 
		
		अगर (flags &  HPEE_FUNCTION_INFO_HAVE_PORT_INIT) अणु
			pos += configure_port_init(buf+pos);
		पूर्ण
		
		अगर (p0 + function_len < pos) अणु
			prपूर्णांकk(KERN_ERR "eisa_enumerator: function %d length mis-match "
			       "got %d, expected %d\n",
			       num_func, pos-p0, function_len);
			res=-1;
			अवरोध;
		पूर्ण
		pos = p0 + function_len;
	पूर्ण
	pr_cont("\n");
	अगर (!id_string_used) अणु
		kमुक्त(board);
	पूर्ण
	
	अगर (pos != es->config_data_length) अणु
		prपूर्णांकk(KERN_ERR "eisa_enumerator: config data length mis-match got %d, expected %d\n",
			pos, es->config_data_length);
		res=-1;
	पूर्ण
	
	अगर (num_func != es->num_functions) अणु
		prपूर्णांकk(KERN_ERR "eisa_enumerator: number of functions mis-match got %d, expected %d\n",
			num_func, es->num_functions);
		res=-2;
	पूर्ण
	
	वापस res;
	
पूर्ण

अटल पूर्णांक init_slot(पूर्णांक slot, काष्ठा eeprom_eisa_slot_info *es)
अणु
	अचिन्हित पूर्णांक id;
	
	अक्षर id_string[8];
	
	अगर (!(es->slot_info&HPEE_SLOT_INFO_NO_READID)) अणु
		/* try to पढ़ो the id of the board in the slot */
		id = le32_to_cpu(inl(SLOT2PORT(slot)+EPI));
		
		अगर (0xffffffff == id) अणु
			/* Maybe we didn't expect a card to be here... */
			अगर (es->eisa_slot_id == 0xffffffff)
				वापस -1;
			
			/* this board is not here or it करोes not 
			 * support पढ़ोid 
			 */
			prपूर्णांकk(KERN_ERR "EISA slot %d a configured board was not detected (", 
			       slot);
			
			prपूर्णांक_eisa_id(id_string, es->eisa_slot_id);
			prपूर्णांकk(" expected %s)\n", id_string);
		
			वापस -1;	

		पूर्ण
		अगर (es->eisa_slot_id != id) अणु
			prपूर्णांक_eisa_id(id_string, id);
			prपूर्णांकk(KERN_ERR "EISA slot %d id mis-match: got %s", 
			       slot, id_string);
			
			prपूर्णांक_eisa_id(id_string, es->eisa_slot_id);
			prपूर्णांकk(" expected %s\n", id_string);
		
			वापस -1;	
			
		पूर्ण
	पूर्ण
	
	/* now: we need to enable the board अगर 
	 * it supports enabling and run through
	 * the port init sction अगर present
	 * and finally record any पूर्णांकerrupt polarity
	 */
	अगर (es->slot_features & HPEE_SLOT_FEATURES_ENABLE) अणु
		/* enable board */
		outb(0x01| inb(SLOT2PORT(slot)+EPI+4),
		     SLOT2PORT(slot)+EPI+4);
	पूर्ण
	
	वापस 0;
पूर्ण


पूर्णांक eisa_क्रमागतerator(अचिन्हित दीर्घ eeprom_addr,
		    काष्ठा resource *io_parent, काष्ठा resource *mem_parent) 
अणु
	पूर्णांक i;
	काष्ठा eeprom_header *eh;
	अटल अक्षर eeprom_buf[HPEE_MAX_LENGTH];
	
	क्रम (i=0; i < HPEE_MAX_LENGTH; i++) अणु
		eeprom_buf[i] = gsc_पढ़ोb(eeprom_addr+i);
	पूर्ण
	
	prपूर्णांकk(KERN_INFO "Enumerating EISA bus\n");
		    	
	eh = (काष्ठा eeprom_header*)(eeprom_buf);
	क्रम (i=0;i<eh->num_slots;i++) अणु
		काष्ठा eeprom_eisa_slot_info *es;
		
		es = (काष्ठा eeprom_eisa_slot_info*)
			(&eeprom_buf[HPEE_SLOT_INFO(i)]);
	        
		अगर (-1==init_slot(i+1, es)) अणु
			जारी;
		पूर्ण
		
		अगर (es->config_data_offset < HPEE_MAX_LENGTH) अणु
			अगर (parse_slot_config(i+1, &eeprom_buf[es->config_data_offset],
					      es, io_parent, mem_parent)) अणु
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk (KERN_WARNING "EISA EEPROM offset 0x%x out of range\n",es->config_data_offset);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस eh->num_slots;
पूर्ण

