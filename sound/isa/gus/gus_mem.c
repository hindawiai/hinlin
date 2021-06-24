<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  GUS's memory allocation routines / bottom layer
 */

#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/info.h>

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम snd_gf1_mem_info_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer);
#पूर्ण_अगर

व्योम snd_gf1_mem_lock(काष्ठा snd_gf1_mem * alloc, पूर्णांक xup)
अणु
	अगर (!xup) अणु
		mutex_lock(&alloc->memory_mutex);
	पूर्ण अन्यथा अणु
		mutex_unlock(&alloc->memory_mutex);
	पूर्ण
पूर्ण

अटल काष्ठा snd_gf1_mem_block *snd_gf1_mem_xalloc(काष्ठा snd_gf1_mem * alloc,
					       काष्ठा snd_gf1_mem_block * block)
अणु
	काष्ठा snd_gf1_mem_block *pblock, *nblock;

	nblock = kदो_स्मृति(माप(काष्ठा snd_gf1_mem_block), GFP_KERNEL);
	अगर (nblock == शून्य)
		वापस शून्य;
	*nblock = *block;
	pblock = alloc->first;
	जबतक (pblock) अणु
		अगर (pblock->ptr > nblock->ptr) अणु
			nblock->prev = pblock->prev;
			nblock->next = pblock;
			pblock->prev = nblock;
			अगर (pblock == alloc->first)
				alloc->first = nblock;
			अन्यथा
				nblock->prev->next = nblock;
			mutex_unlock(&alloc->memory_mutex);
			वापस शून्य;
		पूर्ण
		pblock = pblock->next;
	पूर्ण
	nblock->next = शून्य;
	अगर (alloc->last == शून्य) अणु
		nblock->prev = शून्य;
		alloc->first = alloc->last = nblock;
	पूर्ण अन्यथा अणु
		nblock->prev = alloc->last;
		alloc->last->next = nblock;
		alloc->last = nblock;
	पूर्ण
	वापस nblock;
पूर्ण

पूर्णांक snd_gf1_mem_xमुक्त(काष्ठा snd_gf1_mem * alloc, काष्ठा snd_gf1_mem_block * block)
अणु
	अगर (block->share) अणु	/* ok.. shared block */
		block->share--;
		mutex_unlock(&alloc->memory_mutex);
		वापस 0;
	पूर्ण
	अगर (alloc->first == block) अणु
		alloc->first = block->next;
		अगर (block->next)
			block->next->prev = शून्य;
	पूर्ण अन्यथा अणु
		block->prev->next = block->next;
		अगर (block->next)
			block->next->prev = block->prev;
	पूर्ण
	अगर (alloc->last == block) अणु
		alloc->last = block->prev;
		अगर (block->prev)
			block->prev->next = शून्य;
	पूर्ण अन्यथा अणु
		block->next->prev = block->prev;
		अगर (block->prev)
			block->prev->next = block->next;
	पूर्ण
	kमुक्त(block->name);
	kमुक्त(block);
	वापस 0;
पूर्ण

अटल काष्ठा snd_gf1_mem_block *snd_gf1_mem_look(काष्ठा snd_gf1_mem * alloc,
					     अचिन्हित पूर्णांक address)
अणु
	काष्ठा snd_gf1_mem_block *block;

	क्रम (block = alloc->first; block; block = block->next) अणु
		अगर (block->ptr == address) अणु
			वापस block;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा snd_gf1_mem_block *snd_gf1_mem_share(काष्ठा snd_gf1_mem * alloc,
					      अचिन्हित पूर्णांक *share_id)
अणु
	काष्ठा snd_gf1_mem_block *block;

	अगर (!share_id[0] && !share_id[1] &&
	    !share_id[2] && !share_id[3])
		वापस शून्य;
	क्रम (block = alloc->first; block; block = block->next)
		अगर (!स_भेद(share_id, block->share_id,
				माप(block->share_id)))
			वापस block;
	वापस शून्य;
पूर्ण

अटल पूर्णांक snd_gf1_mem_find(काष्ठा snd_gf1_mem * alloc,
			    काष्ठा snd_gf1_mem_block * block,
			    अचिन्हित पूर्णांक size, पूर्णांक w_16, पूर्णांक align)
अणु
	काष्ठा snd_gf1_bank_info *info = w_16 ? alloc->banks_16 : alloc->banks_8;
	अचिन्हित पूर्णांक idx, boundary;
	पूर्णांक size1;
	काष्ठा snd_gf1_mem_block *pblock;
	अचिन्हित पूर्णांक ptr1, ptr2;

	अगर (w_16 && align < 2)
		align = 2;
	block->flags = w_16 ? SNDRV_GF1_MEM_BLOCK_16BIT : 0;
	block->owner = SNDRV_GF1_MEM_OWNER_DRIVER;
	block->share = 0;
	block->share_id[0] = block->share_id[1] =
	block->share_id[2] = block->share_id[3] = 0;
	block->name = शून्य;
	block->prev = block->next = शून्य;
	क्रम (pblock = alloc->first, idx = 0; pblock; pblock = pblock->next) अणु
		जबतक (pblock->ptr >= (boundary = info[idx].address + info[idx].size))
			idx++;
		जबतक (pblock->ptr + pblock->size >= (boundary = info[idx].address + info[idx].size))
			idx++;
		ptr2 = boundary;
		अगर (pblock->next) अणु
			अगर (pblock->ptr + pblock->size == pblock->next->ptr)
				जारी;
			अगर (pblock->next->ptr < boundary)
				ptr2 = pblock->next->ptr;
		पूर्ण
		ptr1 = ALIGN(pblock->ptr + pblock->size, align);
		अगर (ptr1 >= ptr2)
			जारी;
		size1 = ptr2 - ptr1;
		अगर ((पूर्णांक)size <= size1) अणु
			block->ptr = ptr1;
			block->size = size;
			वापस 0;
		पूर्ण
	पूर्ण
	जबतक (++idx < 4) अणु
		अगर (size <= info[idx].size) अणु
			/* I assume that bank address is alपढ़ोy aligned.. */
			block->ptr = info[idx].address;
			block->size = size;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण

काष्ठा snd_gf1_mem_block *snd_gf1_mem_alloc(काष्ठा snd_gf1_mem * alloc, पूर्णांक owner,
				       अक्षर *name, पूर्णांक size, पूर्णांक w_16, पूर्णांक align,
				       अचिन्हित पूर्णांक *share_id)
अणु
	काष्ठा snd_gf1_mem_block block, *nblock;

	snd_gf1_mem_lock(alloc, 0);
	अगर (share_id != शून्य) अणु
		nblock = snd_gf1_mem_share(alloc, share_id);
		अगर (nblock != शून्य) अणु
			अगर (size != (पूर्णांक)nblock->size) अणु
				/* TODO: हटाओ in the future */
				snd_prपूर्णांकk(KERN_ERR "snd_gf1_mem_alloc - share: sizes differ\n");
				जाओ __std;
			पूर्ण
			nblock->share++;
			snd_gf1_mem_lock(alloc, 1);
			वापस शून्य;
		पूर्ण
	पूर्ण
      __std:
	अगर (snd_gf1_mem_find(alloc, &block, size, w_16, align) < 0) अणु
		snd_gf1_mem_lock(alloc, 1);
		वापस शून्य;
	पूर्ण
	अगर (share_id != शून्य)
		स_नकल(&block.share_id, share_id, माप(block.share_id));
	block.owner = owner;
	block.name = kstrdup(name, GFP_KERNEL);
	nblock = snd_gf1_mem_xalloc(alloc, &block);
	snd_gf1_mem_lock(alloc, 1);
	वापस nblock;
पूर्ण

पूर्णांक snd_gf1_mem_मुक्त(काष्ठा snd_gf1_mem * alloc, अचिन्हित पूर्णांक address)
अणु
	पूर्णांक result;
	काष्ठा snd_gf1_mem_block *block;

	snd_gf1_mem_lock(alloc, 0);
	अगर ((block = snd_gf1_mem_look(alloc, address)) != शून्य) अणु
		result = snd_gf1_mem_xमुक्त(alloc, block);
		snd_gf1_mem_lock(alloc, 1);
		वापस result;
	पूर्ण
	snd_gf1_mem_lock(alloc, 1);
	वापस -EINVAL;
पूर्ण

पूर्णांक snd_gf1_mem_init(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_gf1_mem *alloc;
	काष्ठा snd_gf1_mem_block block;

	alloc = &gus->gf1.mem_alloc;
	mutex_init(&alloc->memory_mutex);
	alloc->first = alloc->last = शून्य;
	अगर (!gus->gf1.memory)
		वापस 0;

	स_रखो(&block, 0, माप(block));
	block.owner = SNDRV_GF1_MEM_OWNER_DRIVER;
	अगर (gus->gf1.enh_mode) अणु
		block.ptr = 0;
		block.size = 1024;
		block.name = kstrdup("InterWave LFOs", GFP_KERNEL);
		अगर (snd_gf1_mem_xalloc(alloc, &block) == शून्य)
			वापस -ENOMEM;
	पूर्ण
	block.ptr = gus->gf1.शेष_voice_address;
	block.size = 4;
	block.name = kstrdup("Voice default (NULL's)", GFP_KERNEL);
	अगर (snd_gf1_mem_xalloc(alloc, &block) == शून्य)
		वापस -ENOMEM;
#अगर_घोषित CONFIG_SND_DEBUG
	snd_card_ro_proc_new(gus->card, "gusmem", gus, snd_gf1_mem_info_पढ़ो);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक snd_gf1_mem_करोne(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_gf1_mem *alloc;
	काष्ठा snd_gf1_mem_block *block, *nblock;

	alloc = &gus->gf1.mem_alloc;
	block = alloc->first;
	जबतक (block) अणु
		nblock = block->next;
		snd_gf1_mem_xमुक्त(alloc, block);
		block = nblock;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम snd_gf1_mem_info_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_gus_card *gus;
	काष्ठा snd_gf1_mem *alloc;
	काष्ठा snd_gf1_mem_block *block;
	अचिन्हित पूर्णांक total, used;
	पूर्णांक i;

	gus = entry->निजी_data;
	alloc = &gus->gf1.mem_alloc;
	mutex_lock(&alloc->memory_mutex);
	snd_iम_लिखो(buffer, "8-bit banks       : \n    ");
	क्रम (i = 0; i < 4; i++)
		snd_iम_लिखो(buffer, "0x%06x (%04ik)%s", alloc->banks_8[i].address, alloc->banks_8[i].size >> 10, i + 1 < 4 ? "," : "");
	snd_iम_लिखो(buffer, "\n"
		    "16-bit banks      : \n    ");
	क्रम (i = total = 0; i < 4; i++) अणु
		snd_iम_लिखो(buffer, "0x%06x (%04ik)%s", alloc->banks_16[i].address, alloc->banks_16[i].size >> 10, i + 1 < 4 ? "," : "");
		total += alloc->banks_16[i].size;
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
	used = 0;
	क्रम (block = alloc->first, i = 0; block; block = block->next, i++) अणु
		used += block->size;
		snd_iम_लिखो(buffer, "Block %i onboard 0x%x size %i (0x%x):\n", i, block->ptr, block->size, block->size);
		अगर (block->share ||
		    block->share_id[0] || block->share_id[1] ||
		    block->share_id[2] || block->share_id[3])
			snd_iम_लिखो(buffer, "  Share           : %i [id0 0x%x] [id1 0x%x] [id2 0x%x] [id3 0x%x]\n",
				block->share,
				block->share_id[0], block->share_id[1],
				block->share_id[2], block->share_id[3]);
		snd_iम_लिखो(buffer, "  Flags           :%s\n",
		block->flags & SNDRV_GF1_MEM_BLOCK_16BIT ? " 16-bit" : "");
		snd_iम_लिखो(buffer, "  Owner           : ");
		चयन (block->owner) अणु
		हाल SNDRV_GF1_MEM_OWNER_DRIVER:
			snd_iम_लिखो(buffer, "driver - %s\n", block->name);
			अवरोध;
		हाल SNDRV_GF1_MEM_OWNER_WAVE_SIMPLE:
			snd_iम_लिखो(buffer, "SIMPLE wave\n");
			अवरोध;
		हाल SNDRV_GF1_MEM_OWNER_WAVE_GF1:
			snd_iम_लिखो(buffer, "GF1 wave\n");
			अवरोध;
		हाल SNDRV_GF1_MEM_OWNER_WAVE_IWFFFF:
			snd_iम_लिखो(buffer, "IWFFFF wave\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
		पूर्ण
	पूर्ण
	snd_iम_लिखो(buffer, "  Total: memory = %i, used = %i, free = %i\n",
		    total, used, total - used);
	mutex_unlock(&alloc->memory_mutex);
#अगर 0
	ultra_iम_लिखो(buffer, "  Verify: free = %i, max 8-bit block = %i, max 16-bit block = %i\n",
		      ultra_memory_मुक्त_size(card, &card->gf1.mem_alloc),
		  ultra_memory_मुक्त_block(card, &card->gf1.mem_alloc, 0),
		 ultra_memory_मुक्त_block(card, &card->gf1.mem_alloc, 1));
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर
