<शैली गुरु>
/*
 * Copyright तऊ 2016 Collabora Ltd.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __DRM_DEBUGFS_CRC_H__
#घोषणा __DRM_DEBUGFS_CRC_H__

#घोषणा DRM_MAX_CRC_NR		10

/**
 * काष्ठा drm_crtc_crc_entry - entry describing a frame's content
 * @has_frame_counter: whether the source was able to provide a frame number
 * @frame: number of the frame this CRC is about, अगर @has_frame_counter is true
 * @crc: array of values that अक्षरacterize the frame
 */
काष्ठा drm_crtc_crc_entry अणु
	bool has_frame_counter;
	uपूर्णांक32_t frame;
	uपूर्णांक32_t crcs[DRM_MAX_CRC_NR];
पूर्ण;

#घोषणा DRM_CRC_ENTRIES_NR	128

/**
 * काष्ठा drm_crtc_crc - data supporting CRC capture on a given CRTC
 * @lock: protects the fields in this काष्ठा
 * @source: name of the currently configured source of CRCs
 * @खोलोed: whether userspace has खोलोed the data file क्रम पढ़ोing
 * @overflow: whether an overflow occured.
 * @entries: array of entries, with size of %DRM_CRC_ENTRIES_NR
 * @head: head of circular queue
 * @tail: tail of circular queue
 * @values_cnt: number of CRC values per entry, up to %DRM_MAX_CRC_NR
 * @wq: workqueue used to synchronize पढ़ोing and writing
 */
काष्ठा drm_crtc_crc अणु
	spinlock_t lock;
	स्थिर अक्षर *source;
	bool खोलोed, overflow;
	काष्ठा drm_crtc_crc_entry *entries;
	पूर्णांक head, tail;
	माप_प्रकार values_cnt;
	रुको_queue_head_t wq;
पूर्ण;

#अगर defined(CONFIG_DEBUG_FS)
पूर्णांक drm_crtc_add_crc_entry(काष्ठा drm_crtc *crtc, bool has_frame,
			   uपूर्णांक32_t frame, uपूर्णांक32_t *crcs);
#अन्यथा
अटल अंतरभूत पूर्णांक drm_crtc_add_crc_entry(काष्ठा drm_crtc *crtc, bool has_frame,
					 uपूर्णांक32_t frame, uपूर्णांक32_t *crcs)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_DEBUG_FS) */

#पूर्ण_अगर /* __DRM_DEBUGFS_CRC_H__ */
