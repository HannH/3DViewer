/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scenemodifier.h"

#include <QtCore/QDebug>

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
}

SceneModifier::~SceneModifier()
{
	clearAllEntity();
	m_rootEntity = nullptr, m_pointCloudEntity = nullptr;
};
void SceneModifier::enableSphere(bool enabled)
{
    m_pointCloudEntity->setParent(enabled ? m_rootEntity : Q_NULLPTR);
}

void SceneModifier::addPoint(const QVector3D& Point, int Radius){
	// Sphere shape data
	Qt3DRender::QSphereMesh *sphereMesh = new Qt3DRender::QSphereMesh();
	sphereMesh->setRings(20);
	sphereMesh->setSlices(20);
	sphereMesh->setRadius(2);

	// Sphere mesh transform
	Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

	sphereTransform->setScale(1.0f);
	sphereTransform->setTranslation(Point);

	Qt3DRender::QPhongMaterial *sphereMaterial = new Qt3DRender::QPhongMaterial();
	sphereMaterial->setDiffuse(QColor(QRgb(0xa69929)));

	// Sphere
	m_pointCloudEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_pointCloudEntity->addComponent(sphereMesh);
	m_pointCloudEntity->addComponent(sphereMaterial);
	m_pointCloudEntity->addComponent(sphereTransform);
}