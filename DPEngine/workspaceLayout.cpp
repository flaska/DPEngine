#include <workspaceLayout.h>
#include <cimage.h>
#include <cworkspace.h>
//#include <cobject.h>
#include <cimage.h>


MWorkspaceLayout::~MWorkspaceLayout()

{}
 void MWorkspaceLayout::ImageResizedAlignToWorkspace(CImage *image)
{
	QPointF newSize=image->GetSize();

	//align to workspace borders
	QRect rect = iParentWorkspace->GetInnerRect();
	//align to workspace borders
	if((image->GetSize().x() + image->GetPosition().x())> rect.right())
	{
		newSize.setX(rect.right()-image->GetPosition().x());
	}
	
	if((image->GetSize().y() + image->GetPosition().y())>  rect.bottom())
	{
		newSize.setY(rect.bottom()-image->GetPosition().y());
	}
	image->SetSize(newSize);
}

 void MWorkspaceLayout::ImageResizedAlignToOtherImages(CImage *image)
{
	QPointF newSize=image->GetSize();
	//align to top of other image
	//align to left side of other image
	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	while (images.hasNext())
	{

		CImage *im = images.next();
		if (im!=image)
		{
			//align to top of other image
			if(IsInRange(im->GetPosition().y(),image->GetPosition().y()+image->GetSize().y(),10))
			{
				newSize.setY(im->GetPosition().y()-image->GetPosition().y());
			}
			//align to left side of other image
			if(IsInRange(im->GetPosition().x(),image->GetPosition().x()+image->GetSize().x(),10))
			{
				newSize.setX(im->GetPosition().x()-image->GetPosition().x());
			}

			//align to bottom of other image
			if(IsInRange(im->GetPosition().y()+im->GetSize().y(),image->GetPosition().y()+image->GetSize().y(),10))
			{
				newSize.setY(im->GetPosition().y()+im->GetSize().y()-image->GetPosition().y());
			}
			//align to right side of other image
			if(IsInRange(im->GetPosition().x()+im->GetSize().x(),image->GetPosition().x()+image->GetSize().x(),10))
			{
				newSize.setX(im->GetPosition().x()+im->GetSize().x()-image->GetPosition().x());
			}
		}
	}
	image->SetSize(newSize);
}
/**
* align image to workspace border
*/
 void MWorkspaceLayout::ImageMovedAlignToWorkspace(CImage *image)
{
	QPointF newPos=image->GetPosition();
	QRect rect = iParentWorkspace->GetInnerRect();
	//align to workspace borders
	if((image->GetSize().x() + image->GetPosition().x())> rect.right())
	{
		newPos.setX(rect.right()-image->GetSize().x());
	}
	if((image->GetSize().y() + image->GetPosition().y())> rect.bottom())
	{
		newPos.setY(rect.bottom()-image->GetSize().y());
	}
	if((image->GetPosition().x())< rect.left())
	{
		newPos.setX( rect.left());
	}
	if((image->GetPosition().y())< rect.top())
	{
		newPos.setY(rect.top());
	}
	/*if((image->GetSize().x() + image->GetPosition().x())> iParentWorkspace->GetSize().x())
	{
		newPos.setX(iParentWorkspace->GetSize().x()-image->GetSize().x());
	}
	if((image->GetSize().y() + image->GetPosition().y())> iParentWorkspace->GetSize().y())
	{
		newPos.setY(iParentWorkspace->GetSize().y()-image->GetSize().y());
	}
	if((image->GetPosition().x())< 0)
	{
		newPos.setX(0);
	}
	if((image->GetPosition().y())< 0)
	{
		newPos.setY(0);
	}*/
	image->SetPosition(newPos);
}

/**
* align image to other images in workspace
*/
 void MWorkspaceLayout::ImageMovedAlignToOtherImages(CImage *image)
{
	QPointF newPos=image->GetPosition();
	//align position to other image borders
	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	while (images.hasNext())
	{

		CImage *im = images.next();
		if (im!=image)
		{
			//align to top of other image
			if(IsInRange(im->GetPosition().y(),image->GetPosition().y(),10))
			{
				newPos.setY(im->GetPosition().y());
			}
			//align to left side of other image
			if(IsInRange(im->GetPosition().x(),image->GetPosition().x(),10))
			{
				newPos.setX(im->GetPosition().x());
			}

			//align to bottom of other image
			if(IsInRange(im->GetPosition().y()+im->GetSize().y(),image->GetPosition().y(),10))
			{
				newPos.setY(im->GetPosition().y()+im->GetSize().y());
			}
			//align to right side of other image
			if(IsInRange(im->GetPosition().x()+im->GetSize().x(),image->GetPosition().x(),10))
			{
				newPos.setX(im->GetPosition().x()+im->GetSize().x());
			}
		}
	}
	//align position + size to other image borders
	images.toFront();
	while (images.hasNext())
	{

		CImage *im = images.next();
		if (im!=image)
		{
			//align to top of other image
			if(IsInRange(im->GetPosition().y(),image->GetPosition().y()+image->GetSize().y(),10))
			{
				newPos.setY(im->GetPosition().y()-image->GetSize().y());
			}
			//align to left side of other image
			if(IsInRange(im->GetPosition().x(),image->GetPosition().x()+image->GetSize().x(),10))
			{
				newPos.setX(im->GetPosition().x()-image->GetSize().x());
			}

			//align to bottom of other image
			if(IsInRange(im->GetPosition().y()+im->GetSize().y(),image->GetPosition().y()+image->GetSize().y(),10))
			{
				newPos.setY(im->GetPosition().y()+im->GetSize().y()-image->GetSize().y());
			}
			//align to right side of other image
			if(IsInRange(im->GetPosition().x()+im->GetSize().x(),image->GetPosition().x()+image->GetSize().x(),10))
			{
				newPos.setX(im->GetPosition().x()+im->GetSize().x()-image->GetSize().x());
			}
		}
	}

	image->SetPosition(newPos);
}

 bool MWorkspaceLayout::IsInRange(int a, int b, int tolerance)
{
	if((a-tolerance<b) && (a+tolerance >b))
		return true;
	return false;
}

