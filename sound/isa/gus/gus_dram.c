<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  DRAM access routines
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/info.h>


अटल पूर्णांक snd_gus_dram_poke(काष्ठा snd_gus_card *gus, अक्षर __user *_buffer,
			     अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size1, size2;
	अक्षर buffer[256], *pbuffer;

	जबतक (size > 0) अणु
		size1 = size > माप(buffer) ? माप(buffer) : size;
		अगर (copy_from_user(buffer, _buffer, size1))
			वापस -EFAULT;
		अगर (gus->पूर्णांकerwave) अणु
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);
			snd_gf1_dram_addr(gus, address);
			outsb(GUSP(gus, DRAM), buffer, size1);
			spin_unlock_irqrestore(&gus->reg_lock, flags);
			address += size1;
		पूर्ण अन्यथा अणु
			pbuffer = buffer;
			size2 = size1;
			जबतक (size2--)
				snd_gf1_poke(gus, address++, *pbuffer++);
		पूर्ण
		size -= size1;
		_buffer += size1;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक snd_gus_dram_ग_लिखो(काष्ठा snd_gus_card *gus, अक्षर __user *buffer,
		       अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक size)
अणु
	वापस snd_gus_dram_poke(gus, buffer, address, size);
पूर्ण

अटल पूर्णांक snd_gus_dram_peek(काष्ठा snd_gus_card *gus, अक्षर __user *_buffer,
			     अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक size,
			     पूर्णांक rom)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size1, size2;
	अक्षर buffer[256], *pbuffer;

	जबतक (size > 0) अणु
		size1 = size > माप(buffer) ? माप(buffer) : size;
		अगर (gus->पूर्णांकerwave) अणु
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, rom ? 0x03 : 0x01);
			snd_gf1_dram_addr(gus, address);
			insb(GUSP(gus, DRAM), buffer, size1);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);
			spin_unlock_irqrestore(&gus->reg_lock, flags);
			address += size1;
		पूर्ण अन्यथा अणु
			pbuffer = buffer;
			size2 = size1;
			जबतक (size2--)
				*pbuffer++ = snd_gf1_peek(gus, address++);
		पूर्ण
		अगर (copy_to_user(_buffer, buffer, size1))
			वापस -EFAULT;
		size -= size1;
		_buffer += size1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_gus_dram_पढ़ो(काष्ठा snd_gus_card *gus, अक्षर __user *buffer,
		      अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक size,
		      पूर्णांक rom)
अणु
	वापस snd_gus_dram_peek(gus, buffer, address, size, rom);
पूर्ण
