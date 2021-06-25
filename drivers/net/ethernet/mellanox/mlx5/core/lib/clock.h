<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#अगर_अघोषित __LIB_CLOCK_H__
#घोषणा __LIB_CLOCK_H__

अटल अंतरभूत bool mlx5_is_real_समय_rq(काष्ठा mlx5_core_dev *mdev)
अणु
	u8 rq_ts_क्रमmat_cap = MLX5_CAP_GEN(mdev, rq_ts_क्रमmat);

	वापस (rq_ts_क्रमmat_cap == MLX5_RQ_TIMESTAMP_FORMAT_CAP_REAL_TIME  ||
		rq_ts_क्रमmat_cap == MLX5_RQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING_AND_REAL_TIME);
पूर्ण

अटल अंतरभूत bool mlx5_is_real_समय_sq(काष्ठा mlx5_core_dev *mdev)
अणु
	u8 sq_ts_क्रमmat_cap = MLX5_CAP_GEN(mdev, sq_ts_क्रमmat);

	वापस (sq_ts_क्रमmat_cap == MLX5_SQ_TIMESTAMP_FORMAT_CAP_REAL_TIME  ||
		sq_ts_क्रमmat_cap == MLX5_SQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING_AND_REAL_TIME);
पूर्ण

प्रकार kसमय_प्रकार (*cqe_ts_to_ns)(काष्ठा mlx5_घड़ी *, u64);

#अगर IS_ENABLED(CONFIG_PTP_1588_CLOCK)
व्योम mlx5_init_घड़ी(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_cleanup_घड़ी(काष्ठा mlx5_core_dev *mdev);

अटल अंतरभूत पूर्णांक mlx5_घड़ी_get_ptp_index(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mdev->घड़ी.ptp ? ptp_घड़ी_index(mdev->घड़ी.ptp) : -1;
पूर्ण

अटल अंतरभूत kसमय_प्रकार mlx5_समयcounter_cyc2समय(काष्ठा mlx5_घड़ी *घड़ी,
						u64 बारtamp)
अणु
	काष्ठा mlx5_समयr *समयr = &घड़ी->समयr;
	अचिन्हित पूर्णांक seq;
	u64 nsec;

	करो अणु
		seq = पढ़ो_seqbegin(&घड़ी->lock);
		nsec = समयcounter_cyc2समय(&समयr->tc, बारtamp);
	पूर्ण जबतक (पढ़ो_seqretry(&घड़ी->lock, seq));

	वापस ns_to_kसमय(nsec);
पूर्ण

#घोषणा REAL_TIME_TO_NS(hi, low) (((u64)hi) * NSEC_PER_SEC + ((u64)low))

अटल अंतरभूत kसमय_प्रकार mlx5_real_समय_cyc2समय(काष्ठा mlx5_घड़ी *घड़ी,
					      u64 बारtamp)
अणु
	u64 समय = REAL_TIME_TO_NS(बारtamp >> 32, बारtamp & 0xFFFFFFFF);

	वापस ns_to_kसमय(समय);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mlx5_init_घड़ी(काष्ठा mlx5_core_dev *mdev) अणुपूर्ण
अटल अंतरभूत व्योम mlx5_cleanup_घड़ी(काष्ठा mlx5_core_dev *mdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5_घड़ी_get_ptp_index(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत kसमय_प्रकार mlx5_समयcounter_cyc2समय(काष्ठा mlx5_घड़ी *घड़ी,
						u64 बारtamp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत kसमय_प्रकार mlx5_real_समय_cyc2समय(काष्ठा mlx5_घड़ी *घड़ी,
					      u64 बारtamp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत cqe_ts_to_ns mlx5_rq_ts_translator(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_is_real_समय_rq(mdev) ? mlx5_real_समय_cyc2समय :
					    mlx5_समयcounter_cyc2समय;
पूर्ण

अटल अंतरभूत cqe_ts_to_ns mlx5_sq_ts_translator(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_is_real_समय_sq(mdev) ? mlx5_real_समय_cyc2समय :
					    mlx5_समयcounter_cyc2समय;
पूर्ण
#पूर्ण_अगर
