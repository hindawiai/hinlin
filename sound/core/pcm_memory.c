<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/पन.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश "pcm_local.h"

अटल पूर्णांक pपुनः_स्मृतिate_dma = 1;
module_param(pपुनः_स्मृतिate_dma, पूर्णांक, 0444);
MODULE_PARM_DESC(pपुनः_स्मृतिate_dma, "Preallocate DMA memory when the PCM devices are initialized.");

अटल पूर्णांक maximum_substreams = 4;
module_param(maximum_substreams, पूर्णांक, 0444);
MODULE_PARM_DESC(maximum_substreams, "Maximum substreams with preallocated DMA memory.");

अटल स्थिर माप_प्रकार snd_minimum_buffer = 16384;

अटल अचिन्हित दीर्घ max_alloc_per_card = 32UL * 1024UL * 1024UL;
module_param(max_alloc_per_card, uदीर्घ, 0644);
MODULE_PARM_DESC(max_alloc_per_card, "Max total allocation bytes per card.");

अटल पूर्णांक करो_alloc_pages(काष्ठा snd_card *card, पूर्णांक type, काष्ठा device *dev,
			  माप_प्रकार size, काष्ठा snd_dma_buffer *dmab)
अणु
	पूर्णांक err;

	अगर (max_alloc_per_card &&
	    card->total_pcm_alloc_bytes + size > max_alloc_per_card)
		वापस -ENOMEM;

	err = snd_dma_alloc_pages(type, dev, size, dmab);
	अगर (!err) अणु
		mutex_lock(&card->memory_mutex);
		card->total_pcm_alloc_bytes += dmab->bytes;
		mutex_unlock(&card->memory_mutex);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम करो_मुक्त_pages(काष्ठा snd_card *card, काष्ठा snd_dma_buffer *dmab)
अणु
	अगर (!dmab->area)
		वापस;
	mutex_lock(&card->memory_mutex);
	WARN_ON(card->total_pcm_alloc_bytes < dmab->bytes);
	card->total_pcm_alloc_bytes -= dmab->bytes;
	mutex_unlock(&card->memory_mutex);
	snd_dma_मुक्त_pages(dmab);
	dmab->area = शून्य;
पूर्ण

/*
 * try to allocate as the large pages as possible.
 * stores the resultant memory size in *res_size.
 *
 * the minimum size is snd_minimum_buffer.  it should be घातer of 2.
 */
अटल पूर्णांक pपुनः_स्मृतिate_pcm_pages(काष्ठा snd_pcm_substream *substream, माप_प्रकार size)
अणु
	काष्ठा snd_dma_buffer *dmab = &substream->dma_buffer;
	काष्ठा snd_card *card = substream->pcm->card;
	माप_प्रकार orig_size = size;
	पूर्णांक err;

	करो अणु
		err = करो_alloc_pages(card, dmab->dev.type, dmab->dev.dev,
				     size, dmab);
		अगर (err != -ENOMEM)
			वापस err;
		size >>= 1;
	पूर्ण जबतक (size >= snd_minimum_buffer);
	dmab->bytes = 0; /* tell error */
	pr_warn("ALSA pcmC%dD%d%c,%d:%s: cannot preallocate for size %zu\n",
		substream->pcm->card->number, substream->pcm->device,
		substream->stream ? 'c' : 'p', substream->number,
		substream->pcm->name, orig_size);
	वापस 0;
पूर्ण

/**
 * snd_pcm_lib_pपुनः_स्मृतिate_मुक्त - release the pपुनः_स्मृतिated buffer of the specअगरied substream.
 * @substream: the pcm substream instance
 *
 * Releases the pre-allocated buffer of the given substream.
 */
व्योम snd_pcm_lib_pपुनः_स्मृतिate_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	करो_मुक्त_pages(substream->pcm->card, &substream->dma_buffer);
पूर्ण

/**
 * snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all - release all pre-allocated buffers on the pcm
 * @pcm: the pcm instance
 *
 * Releases all the pre-allocated buffers on the given pcm.
 */
व्योम snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक stream;

	क्रम_each_pcm_substream(pcm, stream, substream)
		snd_pcm_lib_pपुनः_स्मृतिate_मुक्त(substream);
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all);

#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
/*
 * पढ़ो callback क्रम pपुनः_स्मृति proc file
 *
 * prपूर्णांकs the current allocated size in kB.
 */
अटल व्योम snd_pcm_lib_pपुनः_स्मृतिate_proc_पढ़ो(काष्ठा snd_info_entry *entry,
					      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	snd_iम_लिखो(buffer, "%lu\n", (अचिन्हित दीर्घ) substream->dma_buffer.bytes / 1024);
पूर्ण

/*
 * पढ़ो callback क्रम pपुनः_स्मृति_max proc file
 *
 * prपूर्णांकs the maximum allowed size in kB.
 */
अटल व्योम snd_pcm_lib_pपुनः_स्मृतिate_max_proc_पढ़ो(काष्ठा snd_info_entry *entry,
						  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	snd_iम_लिखो(buffer, "%lu\n", (अचिन्हित दीर्घ) substream->dma_max / 1024);
पूर्ण

/*
 * ग_लिखो callback क्रम pपुनः_स्मृति proc file
 *
 * accepts the pपुनः_स्मृतिation size in kB.
 */
अटल व्योम snd_pcm_lib_pपुनः_स्मृतिate_proc_ग_लिखो(काष्ठा snd_info_entry *entry,
					       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	काष्ठा snd_card *card = substream->pcm->card;
	अक्षर line[64], str[64];
	माप_प्रकार size;
	काष्ठा snd_dma_buffer new_dmab;

	अगर (substream->runसमय) अणु
		buffer->error = -EBUSY;
		वापस;
	पूर्ण
	अगर (!snd_info_get_line(buffer, line, माप(line))) अणु
		snd_info_get_str(str, line, माप(str));
		size = simple_म_से_अदीर्घ(str, शून्य, 10) * 1024;
		अगर ((size != 0 && size < 8192) || size > substream->dma_max) अणु
			buffer->error = -EINVAL;
			वापस;
		पूर्ण
		अगर (substream->dma_buffer.bytes == size)
			वापस;
		स_रखो(&new_dmab, 0, माप(new_dmab));
		new_dmab.dev = substream->dma_buffer.dev;
		अगर (size > 0) अणु
			अगर (करो_alloc_pages(card,
					   substream->dma_buffer.dev.type,
					   substream->dma_buffer.dev.dev,
					   size, &new_dmab) < 0) अणु
				buffer->error = -ENOMEM;
				pr_debug("ALSA pcmC%dD%d%c,%d:%s: cannot preallocate for size %zu\n",
					 substream->pcm->card->number, substream->pcm->device,
					 substream->stream ? 'c' : 'p', substream->number,
					 substream->pcm->name, size);
				वापस;
			पूर्ण
			substream->buffer_bytes_max = size;
		पूर्ण अन्यथा अणु
			substream->buffer_bytes_max = अच_पूर्णांक_उच्च;
		पूर्ण
		अगर (substream->dma_buffer.area)
			करो_मुक्त_pages(card, &substream->dma_buffer);
		substream->dma_buffer = new_dmab;
	पूर्ण अन्यथा अणु
		buffer->error = -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pपुनः_स्मृतिate_info_init(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(substream->pcm->card, "prealloc",
					   substream->proc_root);
	अगर (entry) अणु
		snd_info_set_text_ops(entry, substream,
				      snd_pcm_lib_pपुनः_स्मृतिate_proc_पढ़ो);
		entry->c.text.ग_लिखो = snd_pcm_lib_pपुनः_स्मृतिate_proc_ग_लिखो;
		entry->mode |= 0200;
	पूर्ण
	entry = snd_info_create_card_entry(substream->pcm->card, "prealloc_max",
					   substream->proc_root);
	अगर (entry)
		snd_info_set_text_ops(entry, substream,
				      snd_pcm_lib_pपुनः_स्मृतिate_max_proc_पढ़ो);
पूर्ण

#अन्यथा /* !CONFIG_SND_VERBOSE_PROCFS */
अटल अंतरभूत व्योम pपुनः_स्मृतिate_info_init(काष्ठा snd_pcm_substream *substream)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_VERBOSE_PROCFS */

/*
 * pre-allocate the buffer and create a proc file क्रम the substream
 */
अटल व्योम pपुनः_स्मृतिate_pages(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक type, काष्ठा device *data,
			      माप_प्रकार size, माप_प्रकार max, bool managed)
अणु
	अगर (snd_BUG_ON(substream->dma_buffer.dev.type))
		वापस;

	substream->dma_buffer.dev.type = type;
	substream->dma_buffer.dev.dev = data;

	अगर (size > 0 && pपुनः_स्मृतिate_dma && substream->number < maximum_substreams)
		pपुनः_स्मृतिate_pcm_pages(substream, size);

	अगर (substream->dma_buffer.bytes > 0)
		substream->buffer_bytes_max = substream->dma_buffer.bytes;
	substream->dma_max = max;
	अगर (max > 0)
		pपुनः_स्मृतिate_info_init(substream);
	अगर (managed)
		substream->managed_buffer_alloc = 1;
पूर्ण

अटल व्योम pपुनः_स्मृतिate_pages_क्रम_all(काष्ठा snd_pcm *pcm, पूर्णांक type,
				      व्योम *data, माप_प्रकार size, माप_प्रकार max,
				      bool managed)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक stream;

	क्रम_each_pcm_substream(pcm, stream, substream)
		pपुनः_स्मृतिate_pages(substream, type, data, size, max, managed);
पूर्ण

/**
 * snd_pcm_lib_pपुनः_स्मृतिate_pages - pre-allocation क्रम the given DMA type
 * @substream: the pcm substream instance
 * @type: DMA type (SNDRV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the requested pre-allocation size in bytes
 * @max: the max. allowed pre-allocation size
 *
 * Do pre-allocation क्रम the given DMA buffer type.
 */
व्योम snd_pcm_lib_pपुनः_स्मृतिate_pages(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक type, काष्ठा device *data,
				  माप_प्रकार size, माप_प्रकार max)
अणु
	pपुनः_स्मृतिate_pages(substream, type, data, size, max, false);
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_pपुनः_स्मृतिate_pages);

/**
 * snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all - pre-allocation क्रम continuous memory type (all substreams)
 * @pcm: the pcm instance
 * @type: DMA type (SNDRV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the requested pre-allocation size in bytes
 * @max: the max. allowed pre-allocation size
 *
 * Do pre-allocation to all substreams of the given pcm क्रम the
 * specअगरied DMA type.
 */
व्योम snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(काष्ठा snd_pcm *pcm,
					  पूर्णांक type, व्योम *data,
					  माप_प्रकार size, माप_प्रकार max)
अणु
	pपुनः_स्मृतिate_pages_क्रम_all(pcm, type, data, size, max, false);
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all);

/**
 * snd_pcm_set_managed_buffer - set up buffer management क्रम a substream
 * @substream: the pcm substream instance
 * @type: DMA type (SNDRV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the requested pre-allocation size in bytes
 * @max: the max. allowed pre-allocation size
 *
 * Do pre-allocation क्रम the given DMA buffer type, and set the managed
 * buffer allocation mode to the given substream.
 * In this mode, PCM core will allocate a buffer स्वतःmatically beक्रमe PCM
 * hw_params ops call, and release the buffer after PCM hw_मुक्त ops call
 * as well, so that the driver करोesn't need to invoke the allocation and
 * the release explicitly in its callback.
 * When a buffer is actually allocated beक्रमe the PCM hw_params call, it
 * turns on the runसमय buffer_changed flag क्रम drivers changing their h/w
 * parameters accordingly.
 */
व्योम snd_pcm_set_managed_buffer(काष्ठा snd_pcm_substream *substream, पूर्णांक type,
				काष्ठा device *data, माप_प्रकार size, माप_प्रकार max)
अणु
	pपुनः_स्मृतिate_pages(substream, type, data, size, max, true);
पूर्ण
EXPORT_SYMBOL(snd_pcm_set_managed_buffer);

/**
 * snd_pcm_set_managed_buffer_all - set up buffer management क्रम all substreams
 *	क्रम all substreams
 * @pcm: the pcm instance
 * @type: DMA type (SNDRV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the requested pre-allocation size in bytes
 * @max: the max. allowed pre-allocation size
 *
 * Do pre-allocation to all substreams of the given pcm क्रम the specअगरied DMA
 * type and size, and set the managed_buffer_alloc flag to each substream.
 */
व्योम snd_pcm_set_managed_buffer_all(काष्ठा snd_pcm *pcm, पूर्णांक type,
				    काष्ठा device *data,
				    माप_प्रकार size, माप_प्रकार max)
अणु
	pपुनः_स्मृतिate_pages_क्रम_all(pcm, type, data, size, max, true);
पूर्ण
EXPORT_SYMBOL(snd_pcm_set_managed_buffer_all);

#अगर_घोषित CONFIG_SND_DMA_SGBUF
/*
 * snd_pcm_sgbuf_ops_page - get the page काष्ठा at the given offset
 * @substream: the pcm substream instance
 * @offset: the buffer offset
 *
 * Used as the page callback of PCM ops.
 *
 * Return: The page काष्ठा at the given buffer offset. %शून्य on failure.
 */
काष्ठा page *snd_pcm_sgbuf_ops_page(काष्ठा snd_pcm_substream *substream, अचिन्हित दीर्घ offset)
अणु
	काष्ठा snd_sg_buf *sgbuf = snd_pcm_substream_sgbuf(substream);

	अचिन्हित पूर्णांक idx = offset >> PAGE_SHIFT;
	अगर (idx >= (अचिन्हित पूर्णांक)sgbuf->pages)
		वापस शून्य;
	वापस sgbuf->page_table[idx];
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_DMA_SGBUF */

/**
 * snd_pcm_lib_दो_स्मृति_pages - allocate the DMA buffer
 * @substream: the substream to allocate the DMA buffer to
 * @size: the requested buffer size in bytes
 *
 * Allocates the DMA buffer on the BUS type given earlier to
 * snd_pcm_lib_pपुनः_स्मृतिate_xxx_pages().
 *
 * Return: 1 अगर the buffer is changed, 0 अगर not changed, or a negative
 * code on failure.
 */
पूर्णांक snd_pcm_lib_दो_स्मृति_pages(काष्ठा snd_pcm_substream *substream, माप_प्रकार size)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_dma_buffer *dmab = शून्य;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -EINVAL;
	अगर (snd_BUG_ON(substream->dma_buffer.dev.type ==
		       SNDRV_DMA_TYPE_UNKNOWN))
		वापस -EINVAL;
	runसमय = substream->runसमय;
	card = substream->pcm->card;

	अगर (runसमय->dma_buffer_p) अणु
		/* perphaps, we might मुक्त the large DMA memory region
		   to save some space here, but the actual solution
		   costs us less समय */
		अगर (runसमय->dma_buffer_p->bytes >= size) अणु
			runसमय->dma_bytes = size;
			वापस 0;	/* ok, करो not change */
		पूर्ण
		snd_pcm_lib_मुक्त_pages(substream);
	पूर्ण
	अगर (substream->dma_buffer.area != शून्य &&
	    substream->dma_buffer.bytes >= size) अणु
		dmab = &substream->dma_buffer; /* use the pre-allocated buffer */
	पूर्ण अन्यथा अणु
		dmab = kzalloc(माप(*dmab), GFP_KERNEL);
		अगर (! dmab)
			वापस -ENOMEM;
		dmab->dev = substream->dma_buffer.dev;
		अगर (करो_alloc_pages(card,
				   substream->dma_buffer.dev.type,
				   substream->dma_buffer.dev.dev,
				   size, dmab) < 0) अणु
			kमुक्त(dmab);
			pr_debug("ALSA pcmC%dD%d%c,%d:%s: cannot preallocate for size %zu\n",
				 substream->pcm->card->number, substream->pcm->device,
				 substream->stream ? 'c' : 'p', substream->number,
				 substream->pcm->name, size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	snd_pcm_set_runसमय_buffer(substream, dmab);
	runसमय->dma_bytes = size;
	वापस 1;			/* area was changed */
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_दो_स्मृति_pages);

/**
 * snd_pcm_lib_मुक्त_pages - release the allocated DMA buffer.
 * @substream: the substream to release the DMA buffer
 *
 * Releases the DMA buffer allocated via snd_pcm_lib_दो_स्मृति_pages().
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_lib_मुक्त_pages(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_card *card = substream->pcm->card;
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -EINVAL;
	runसमय = substream->runसमय;
	अगर (runसमय->dma_area == शून्य)
		वापस 0;
	अगर (runसमय->dma_buffer_p != &substream->dma_buffer) अणु
		/* it's a newly allocated buffer.  release it now. */
		करो_मुक्त_pages(card, runसमय->dma_buffer_p);
		kमुक्त(runसमय->dma_buffer_p);
	पूर्ण
	snd_pcm_set_runसमय_buffer(substream, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_मुक्त_pages);

पूर्णांक _snd_pcm_lib_alloc_vदो_स्मृति_buffer(काष्ठा snd_pcm_substream *substream,
				      माप_प्रकार size, gfp_t gfp_flags)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -EINVAL;
	runसमय = substream->runसमय;
	अगर (runसमय->dma_area) अणु
		अगर (runसमय->dma_bytes >= size)
			वापस 0; /* alपढ़ोy large enough */
		vमुक्त(runसमय->dma_area);
	पूर्ण
	runसमय->dma_area = __vदो_स्मृति(size, gfp_flags);
	अगर (!runसमय->dma_area)
		वापस -ENOMEM;
	runसमय->dma_bytes = size;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(_snd_pcm_lib_alloc_vदो_स्मृति_buffer);

/**
 * snd_pcm_lib_मुक्त_vदो_स्मृति_buffer - मुक्त vदो_स्मृति buffer
 * @substream: the substream with a buffer allocated by
 *	snd_pcm_lib_alloc_vदो_स्मृति_buffer()
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_lib_मुक्त_vदो_स्मृति_buffer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -EINVAL;
	runसमय = substream->runसमय;
	vमुक्त(runसमय->dma_area);
	runसमय->dma_area = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_मुक्त_vदो_स्मृति_buffer);

/**
 * snd_pcm_lib_get_vदो_स्मृति_page - map vदो_स्मृति buffer offset to page काष्ठा
 * @substream: the substream with a buffer allocated by
 *	snd_pcm_lib_alloc_vदो_स्मृति_buffer()
 * @offset: offset in the buffer
 *
 * This function is to be used as the page callback in the PCM ops.
 *
 * Return: The page काष्ठा, or %शून्य on failure.
 */
काष्ठा page *snd_pcm_lib_get_vदो_स्मृति_page(काष्ठा snd_pcm_substream *substream,
					  अचिन्हित दीर्घ offset)
अणु
	वापस vदो_स्मृति_to_page(substream->runसमय->dma_area + offset);
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_get_vदो_स्मृति_page);
