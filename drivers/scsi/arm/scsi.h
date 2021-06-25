<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/scsi/scsi.h
 *
 *  Copyright (C) 2002 Russell King
 *
 *  Commonly used scsi driver functions.
 */

#समावेश <linux/scatterlist.h>

#घोषणा BELT_AND_BRACES

/*
 * The scatter-gather list handling.  This contains all
 * the yucky stuff that needs to be fixed properly.
 */

/*
 * copy_SCp_to_sg() Assumes contiguous allocation at @sg of at-most @max
 * entries of uninitialized memory. SCp is from scsi-ml and has a valid
 * (possibly chained) sg-list
 */
अटल अंतरभूत पूर्णांक copy_SCp_to_sg(काष्ठा scatterlist *sg, काष्ठा scsi_poपूर्णांकer *SCp, पूर्णांक max)
अणु
	पूर्णांक bufs = SCp->buffers_residual;

	/* FIXME: It should be easy क्रम drivers to loop on copy_SCp_to_sg().
	 * and to हटाओ this BUG_ON. Use min() in-its-place
	 */
	BUG_ON(bufs + 1 > max);

	sg_set_buf(sg, SCp->ptr, SCp->this_residual);

	अगर (bufs) अणु
		काष्ठा scatterlist *src_sg;
		अचिन्हित i;

		क्रम_each_sg(sg_next(SCp->buffer), src_sg, bufs, i)
			*(++sg) = *src_sg;
		sg_mark_end(sg);
	पूर्ण

	वापस bufs + 1;
पूर्ण

अटल अंतरभूत पूर्णांक next_SCp(काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	पूर्णांक ret = SCp->buffers_residual;
	अगर (ret) अणु
		SCp->buffer = sg_next(SCp->buffer);
		SCp->buffers_residual--;
		SCp->ptr = sg_virt(SCp->buffer);
		SCp->this_residual = SCp->buffer->length;
	पूर्ण अन्यथा अणु
		SCp->ptr = शून्य;
		SCp->this_residual = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर get_next_SCp_byte(काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	अक्षर c = *SCp->ptr;

	SCp->ptr += 1;
	SCp->this_residual -= 1;

	वापस c;
पूर्ण

अटल अंतरभूत व्योम put_next_SCp_byte(काष्ठा scsi_poपूर्णांकer *SCp, अचिन्हित अक्षर c)
अणु
	*SCp->ptr = c;
	SCp->ptr += 1;
	SCp->this_residual -= 1;
पूर्ण

अटल अंतरभूत व्योम init_SCp(काष्ठा scsi_cmnd *SCpnt)
अणु
	स_रखो(&SCpnt->SCp, 0, माप(काष्ठा scsi_poपूर्णांकer));

	अगर (scsi_bufflen(SCpnt)) अणु
		अचिन्हित दीर्घ len = 0;

		SCpnt->SCp.buffer = scsi_sglist(SCpnt);
		SCpnt->SCp.buffers_residual = scsi_sg_count(SCpnt) - 1;
		SCpnt->SCp.ptr = sg_virt(SCpnt->SCp.buffer);
		SCpnt->SCp.this_residual = SCpnt->SCp.buffer->length;
		SCpnt->SCp.phase = scsi_bufflen(SCpnt);

#अगर_घोषित BELT_AND_BRACES
		अणु	/*
			 * Calculate correct buffer length.  Some commands
			 * come in with the wrong scsi_bufflen.
			 */
			काष्ठा scatterlist *sg;
			अचिन्हित i, sg_count = scsi_sg_count(SCpnt);

			scsi_क्रम_each_sg(SCpnt, sg, sg_count, i)
				len += sg->length;

			अगर (scsi_bufflen(SCpnt) != len) अणु
				prपूर्णांकk(KERN_WARNING
				       "scsi%d.%c: bad request buffer "
				       "length %d, should be %ld\n",
					SCpnt->device->host->host_no,
					'0' + SCpnt->device->id,
					scsi_bufflen(SCpnt), len);
				/*
				 * FIXME: Totaly naive fixup. We should पात
				 * with error
				 */
				SCpnt->SCp.phase =
					min_t(अचिन्हित दीर्घ, len,
					      scsi_bufflen(SCpnt));
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		SCpnt->SCp.ptr = शून्य;
		SCpnt->SCp.this_residual = 0;
		SCpnt->SCp.phase = 0;
	पूर्ण
पूर्ण
