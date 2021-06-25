<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>

#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"
#समावेश "lib/eq.h"
#समावेश "fpga/core.h"
#समावेश "fpga/conn.h"

अटल स्थिर अक्षर *स्थिर mlx5_fpga_error_strings[] = अणु
	"Null Syndrome",
	"Corrupted DDR",
	"Flash Timeout",
	"Internal Link Error",
	"Watchdog HW Failure",
	"I2C Failure",
	"Image Changed",
	"Temperature Critical",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mlx5_fpga_qp_error_strings[] = अणु
	"Null Syndrome",
	"Retry Counter Expired",
	"RNR Expired",
पूर्ण;
अटल काष्ठा mlx5_fpga_device *mlx5_fpga_device_alloc(व्योम)
अणु
	काष्ठा mlx5_fpga_device *fdev = शून्य;

	fdev = kzalloc(माप(*fdev), GFP_KERNEL);
	अगर (!fdev)
		वापस शून्य;

	spin_lock_init(&fdev->state_lock);
	fdev->state = MLX5_FPGA_STATUS_NONE;
	वापस fdev;
पूर्ण

अटल स्थिर अक्षर *mlx5_fpga_image_name(क्रमागत mlx5_fpga_image image)
अणु
	चयन (image) अणु
	हाल MLX5_FPGA_IMAGE_USER:
		वापस "user";
	हाल MLX5_FPGA_IMAGE_FACTORY:
		वापस "factory";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *mlx5_fpga_name(u32 fpga_id)
अणु
	अटल अक्षर ret[32];

	चयन (fpga_id) अणु
	हाल MLX5_FPGA_NEWTON:
		वापस "Newton";
	हाल MLX5_FPGA_EDISON:
		वापस "Edison";
	हाल MLX5_FPGA_MORSE:
		वापस "Morse";
	हाल MLX5_FPGA_MORSEQ:
		वापस "MorseQ";
	पूर्ण

	snम_लिखो(ret, माप(ret), "Unknown %d", fpga_id);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_is_fpga_lookaside(u32 fpga_id)
अणु
	वापस fpga_id != MLX5_FPGA_NEWTON && fpga_id != MLX5_FPGA_EDISON;
पूर्ण

अटल पूर्णांक mlx5_fpga_device_load_check(काष्ठा mlx5_fpga_device *fdev)
अणु
	काष्ठा mlx5_fpga_query query;
	पूर्णांक err;

	err = mlx5_fpga_query(fdev->mdev, &query);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to query status: %d\n", err);
		वापस err;
	पूर्ण

	fdev->last_admin_image = query.admin_image;
	fdev->last_oper_image = query.oper_image;

	mlx5_fpga_info(fdev, "Status %u; Admin image %u; Oper image %u\n",
		       query.status, query.admin_image, query.oper_image);

	/* क्रम FPGA lookaside projects FPGA load status is not important */
	अगर (mlx5_is_fpga_lookaside(MLX5_CAP_FPGA(fdev->mdev, fpga_id)))
		वापस 0;

	अगर (query.status != MLX5_FPGA_STATUS_SUCCESS) अणु
		mlx5_fpga_err(fdev, "%s image failed to load; status %u\n",
			      mlx5_fpga_image_name(fdev->last_oper_image),
			      query.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_fpga_device_brb(काष्ठा mlx5_fpga_device *fdev)
अणु
	पूर्णांक err;
	काष्ठा mlx5_core_dev *mdev = fdev->mdev;

	err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_SANDBOX_BYPASS_ON);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to set bypass on: %d\n", err);
		वापस err;
	पूर्ण
	err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_RESET_SANDBOX);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to reset SBU: %d\n", err);
		वापस err;
	पूर्ण
	err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_SANDBOX_BYPASS_OFF);
	अगर (err) अणु
		mlx5_fpga_err(fdev, "Failed to set bypass off: %d\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_fpga_event(काष्ठा mlx5_fpga_device *, अचिन्हित दीर्घ, व्योम *);

अटल पूर्णांक fpga_err_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *eqe)
अणु
	काष्ठा mlx5_fpga_device *fdev = mlx5_nb_cof(nb, काष्ठा mlx5_fpga_device, fpga_err_nb);

	वापस mlx5_fpga_event(fdev, event, eqe);
पूर्ण

अटल पूर्णांक fpga_qp_err_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *eqe)
अणु
	काष्ठा mlx5_fpga_device *fdev = mlx5_nb_cof(nb, काष्ठा mlx5_fpga_device, fpga_qp_err_nb);

	वापस mlx5_fpga_event(fdev, event, eqe);
पूर्ण

पूर्णांक mlx5_fpga_device_start(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	अचिन्हित पूर्णांक max_num_qps;
	अचिन्हित दीर्घ flags;
	u32 fpga_id;
	पूर्णांक err;

	अगर (!fdev)
		वापस 0;

	err = mlx5_fpga_caps(fdev->mdev);
	अगर (err)
		जाओ out;

	err = mlx5_fpga_device_load_check(fdev);
	अगर (err)
		जाओ out;

	fpga_id = MLX5_CAP_FPGA(fdev->mdev, fpga_id);
	mlx5_fpga_info(fdev, "FPGA card %s:%u\n", mlx5_fpga_name(fpga_id), fpga_id);

	/* No QPs अगर FPGA करोes not participate in net processing */
	अगर (mlx5_is_fpga_lookaside(fpga_id))
		जाओ out;

	mlx5_fpga_info(fdev, "%s(%d): image, version %u; SBU %06x:%04x version %d\n",
		       mlx5_fpga_image_name(fdev->last_oper_image),
		       fdev->last_oper_image,
		       MLX5_CAP_FPGA(fdev->mdev, image_version),
		       MLX5_CAP_FPGA(fdev->mdev, ieee_venकरोr_id),
		       MLX5_CAP_FPGA(fdev->mdev, sandbox_product_id),
		       MLX5_CAP_FPGA(fdev->mdev, sandbox_product_version));

	max_num_qps = MLX5_CAP_FPGA(mdev, shell_caps.max_num_qps);
	अगर (!max_num_qps) अणु
		mlx5_fpga_err(fdev, "FPGA reports 0 QPs in SHELL_CAPS\n");
		err = -ENOTSUPP;
		जाओ out;
	पूर्ण

	err = mlx5_core_reserve_gids(mdev, max_num_qps);
	अगर (err)
		जाओ out;

	MLX5_NB_INIT(&fdev->fpga_err_nb, fpga_err_event, FPGA_ERROR);
	MLX5_NB_INIT(&fdev->fpga_qp_err_nb, fpga_qp_err_event, FPGA_QP_ERROR);
	mlx5_eq_notअगरier_रेजिस्टर(fdev->mdev, &fdev->fpga_err_nb);
	mlx5_eq_notअगरier_रेजिस्टर(fdev->mdev, &fdev->fpga_qp_err_nb);

	err = mlx5_fpga_conn_device_init(fdev);
	अगर (err)
		जाओ err_rsvd_gid;

	अगर (fdev->last_oper_image == MLX5_FPGA_IMAGE_USER) अणु
		err = mlx5_fpga_device_brb(fdev);
		अगर (err)
			जाओ err_conn_init;
	पूर्ण

	जाओ out;

err_conn_init:
	mlx5_fpga_conn_device_cleanup(fdev);

err_rsvd_gid:
	mlx5_eq_notअगरier_unरेजिस्टर(fdev->mdev, &fdev->fpga_err_nb);
	mlx5_eq_notअगरier_unरेजिस्टर(fdev->mdev, &fdev->fpga_qp_err_nb);
	mlx5_core_unreserve_gids(mdev, max_num_qps);
out:
	spin_lock_irqsave(&fdev->state_lock, flags);
	fdev->state = err ? MLX5_FPGA_STATUS_FAILURE : MLX5_FPGA_STATUS_SUCCESS;
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	वापस err;
पूर्ण

पूर्णांक mlx5_fpga_init(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = शून्य;

	अगर (!MLX5_CAP_GEN(mdev, fpga)) अणु
		mlx5_core_dbg(mdev, "FPGA capability not present\n");
		वापस 0;
	पूर्ण

	mlx5_core_dbg(mdev, "Initializing FPGA\n");

	fdev = mlx5_fpga_device_alloc();
	अगर (!fdev)
		वापस -ENOMEM;

	fdev->mdev = mdev;
	mdev->fpga = fdev;

	वापस 0;
पूर्ण

व्योम mlx5_fpga_device_stop(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;
	अचिन्हित पूर्णांक max_num_qps;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (!fdev)
		वापस;

	अगर (mlx5_is_fpga_lookaside(MLX5_CAP_FPGA(fdev->mdev, fpga_id)))
		वापस;

	spin_lock_irqsave(&fdev->state_lock, flags);
	अगर (fdev->state != MLX5_FPGA_STATUS_SUCCESS) अणु
		spin_unlock_irqrestore(&fdev->state_lock, flags);
		वापस;
	पूर्ण
	fdev->state = MLX5_FPGA_STATUS_NONE;
	spin_unlock_irqrestore(&fdev->state_lock, flags);

	अगर (fdev->last_oper_image == MLX5_FPGA_IMAGE_USER) अणु
		err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_SANDBOX_BYPASS_ON);
		अगर (err)
			mlx5_fpga_err(fdev, "Failed to re-set SBU bypass on: %d\n",
				      err);
	पूर्ण

	mlx5_fpga_conn_device_cleanup(fdev);
	mlx5_eq_notअगरier_unरेजिस्टर(fdev->mdev, &fdev->fpga_err_nb);
	mlx5_eq_notअगरier_unरेजिस्टर(fdev->mdev, &fdev->fpga_qp_err_nb);

	max_num_qps = MLX5_CAP_FPGA(mdev, shell_caps.max_num_qps);
	mlx5_core_unreserve_gids(mdev, max_num_qps);
पूर्ण

व्योम mlx5_fpga_cleanup(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_fpga_device *fdev = mdev->fpga;

	mlx5_fpga_device_stop(mdev);
	kमुक्त(fdev);
	mdev->fpga = शून्य;
पूर्ण

अटल स्थिर अक्षर *mlx5_fpga_syndrome_to_string(u8 syndrome)
अणु
	अगर (syndrome < ARRAY_SIZE(mlx5_fpga_error_strings))
		वापस mlx5_fpga_error_strings[syndrome];
	वापस "Unknown";
पूर्ण

अटल स्थिर अक्षर *mlx5_fpga_qp_syndrome_to_string(u8 syndrome)
अणु
	अगर (syndrome < ARRAY_SIZE(mlx5_fpga_qp_error_strings))
		वापस mlx5_fpga_qp_error_strings[syndrome];
	वापस "Unknown";
पूर्ण

अटल पूर्णांक mlx5_fpga_event(काष्ठा mlx5_fpga_device *fdev,
			   अचिन्हित दीर्घ event, व्योम *eqe)
अणु
	व्योम *data = ((काष्ठा mlx5_eqe *)eqe)->data.raw;
	स्थिर अक्षर *event_name;
	bool tearकरोwn = false;
	अचिन्हित दीर्घ flags;
	u8 syndrome;

	चयन (event) अणु
	हाल MLX5_EVENT_TYPE_FPGA_ERROR:
		syndrome = MLX5_GET(fpga_error_event, data, syndrome);
		event_name = mlx5_fpga_syndrome_to_string(syndrome);
		अवरोध;
	हाल MLX5_EVENT_TYPE_FPGA_QP_ERROR:
		syndrome = MLX5_GET(fpga_qp_error_event, data, syndrome);
		event_name = mlx5_fpga_qp_syndrome_to_string(syndrome);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	spin_lock_irqsave(&fdev->state_lock, flags);
	चयन (fdev->state) अणु
	हाल MLX5_FPGA_STATUS_SUCCESS:
		mlx5_fpga_warn(fdev, "Error %u: %s\n", syndrome, event_name);
		tearकरोwn = true;
		अवरोध;
	शेष:
		mlx5_fpga_warn_ratelimited(fdev, "Unexpected error event %u: %s\n",
					   syndrome, event_name);
	पूर्ण
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	/* We tear-करोwn the card's पूर्णांकerfaces and functionality because
	 * the FPGA bump-on-the-wire is misbehaving and we lose ability
	 * to communicate with the network. User may still be able to
	 * recover by re-programming or debugging the FPGA
	 */
	अगर (tearकरोwn)
		mlx5_trigger_health_work(fdev->mdev);

	वापस NOTIFY_OK;
पूर्ण
