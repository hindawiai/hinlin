<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/mempool.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "snic_io.h"
#समावेश "snic.h"

/*
 * snic_get_trc_buf : Allocates a trace record and वापसs.
 */
काष्ठा snic_trc_data *
snic_get_trc_buf(व्योम)
अणु
	काष्ठा snic_trc *trc = &snic_glob->trc;
	काष्ठा snic_trc_data *td = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&trc->lock, flags);
	td = &trc->buf[trc->wr_idx];
	trc->wr_idx++;

	अगर (trc->wr_idx == trc->max_idx)
		trc->wr_idx = 0;

	अगर (trc->wr_idx != trc->rd_idx) अणु
		spin_unlock_irqrestore(&trc->lock, flags);

		जाओ end;
	पूर्ण

	trc->rd_idx++;
	अगर (trc->rd_idx == trc->max_idx)
		trc->rd_idx = 0;

	td->ts = 0;	/* Marker क्रम checking the record, क्रम complete data*/
	spin_unlock_irqrestore(&trc->lock, flags);

end:

	वापस td;
पूर्ण /* end of snic_get_trc_buf */

/*
 * snic_fmt_trc_data : Formats trace data क्रम prपूर्णांकing.
 */
अटल पूर्णांक
snic_fmt_trc_data(काष्ठा snic_trc_data *td, अक्षर *buf, पूर्णांक buf_sz)
अणु
	पूर्णांक len = 0;
	काष्ठा बारpec64 पंचांगspec;

	jअगरfies_to_बारpec64(td->ts, &पंचांगspec);

	len += snम_लिखो(buf, buf_sz,
			"%llu.%09lu %-25s %3d %4x %16llx %16llx %16llx %16llx %16llx\n",
			पंचांगspec.tv_sec,
			पंचांगspec.tv_nsec,
			td->fn,
			td->hno,
			td->tag,
			td->data[0], td->data[1], td->data[2], td->data[3],
			td->data[4]);

	वापस len;
पूर्ण /* end of snic_fmt_trc_data */

/*
 * snic_get_trc_data : Returns a क्रमmatted trace buffer.
 */
पूर्णांक
snic_get_trc_data(अक्षर *buf, पूर्णांक buf_sz)
अणु
	काष्ठा snic_trc_data *td = शून्य;
	काष्ठा snic_trc *trc = &snic_glob->trc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&trc->lock, flags);
	अगर (trc->rd_idx == trc->wr_idx) अणु
		spin_unlock_irqrestore(&trc->lock, flags);

		वापस -1;
	पूर्ण
	td = &trc->buf[trc->rd_idx];

	अगर (td->ts == 0) अणु
		/* ग_लिखो in progress. */
		spin_unlock_irqrestore(&trc->lock, flags);

		वापस -1;
	पूर्ण

	trc->rd_idx++;
	अगर (trc->rd_idx == trc->max_idx)
		trc->rd_idx = 0;
	spin_unlock_irqrestore(&trc->lock, flags);

	वापस snic_fmt_trc_data(td, buf, buf_sz);
पूर्ण /* end of snic_get_trc_data */

/*
 * snic_trc_init() : Configures Trace Functionality क्रम snic.
 */
पूर्णांक
snic_trc_init(व्योम)
अणु
	काष्ठा snic_trc *trc = &snic_glob->trc;
	व्योम *tbuf = शून्य;
	पूर्णांक tbuf_sz = 0, ret;

	tbuf_sz = (snic_trace_max_pages * PAGE_SIZE);
	tbuf = vzalloc(tbuf_sz);
	अगर (!tbuf) अणु
		SNIC_ERR("Failed to Allocate Trace Buffer Size. %d\n", tbuf_sz);
		SNIC_ERR("Trace Facility not enabled.\n");
		ret = -ENOMEM;

		वापस ret;
	पूर्ण

	trc->buf = (काष्ठा snic_trc_data *) tbuf;
	spin_lock_init(&trc->lock);

	snic_trc_debugfs_init();

	trc->max_idx = (tbuf_sz / SNIC_TRC_ENTRY_SZ);
	trc->rd_idx = trc->wr_idx = 0;
	trc->enable = true;
	SNIC_INFO("Trace Facility Enabled.\n Trace Buffer SZ %lu Pages.\n",
		  tbuf_sz / PAGE_SIZE);
	ret = 0;

	वापस ret;
पूर्ण /* end of snic_trc_init */

/*
 * snic_trc_मुक्त : Releases the trace buffer and disables the tracing.
 */
व्योम
snic_trc_मुक्त(व्योम)
अणु
	काष्ठा snic_trc *trc = &snic_glob->trc;

	trc->enable = false;
	snic_trc_debugfs_term();

	अगर (trc->buf) अणु
		vमुक्त(trc->buf);
		trc->buf = शून्य;
	पूर्ण

	SNIC_INFO("Trace Facility Disabled.\n");
पूर्ण /* end of snic_trc_मुक्त */
