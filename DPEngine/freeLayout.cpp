#include <freeLayout.h>
#include <cimage.h>
#include <cworkspace.h>

CFreeLayout::CFreeLayout(CWorkspace *parentWorkspace)
{
	iParentWorkspace=parentWorkspace;
}




CFreeLayout::~CFreeLayout()
{

}

void CFreeLayout::Do()
{
}
 void CFreeLayout::RemoveImage(CImage *image)
 {
	//
 }

bool CFreeLayout::PrepareNewImageGeometry(CImage *image)
{
	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	images.toBack();
	if(images.hasPrevious())
	{
		CImage*im= images.previous();
		image->SetPosition(QPointF(iParentWorkspace->GetPosition().x()+iParentWorkspace->GetBorders().left,
			iParentWorkspace->GetPosition().y()+iParentWorkspace->GetBorders().top));
	}


	if(image->GetSize().x() > iParentWorkspace->GetSize().x())
	{
		image->SetGeometry(image->GetPosition().x(),
			image->GetPosition().y(),
			iParentWorkspace->GetSize().x()-iParentWorkspace->GetBorders().right-iParentWorkspace->GetBorders().left,
			iParentWorkspace->GetSize().y()-iParentWorkspace->GetBorders().top-iParentWorkspace->GetBorders().bottom);
	}
	return true;
}
TLayoutType CFreeLayout::GetType()
{
	return ELayoutFree;
}

void CFreeLayout::PrepareImageToMove(CImage *image)
{
	iCurrentImage = image;//being moved resized
	iImageLastPosition=image->GetPosition();
	iImageLastSize=image->GetSize();
}


/**
default layout aligmnment 
1/align image to workspace borders
2/align image to other images in workspace
*/
void CFreeLayout::ImageMoved(CImage *image)
{
	ImageMovedAlignToWorkspace(image);
	ImageMovedAlignToOtherImages(image);

}

/**
* Called after user releaser mouse after moving object
*/
void CFreeLayout::ImageMoveFinished(CImage *image)
{
//default implementation - do nothing

}

void CFreeLayout::PrepareImageToResize(CImage *image)
{
	iCurrentImage = image;//being moved resized
	iImageLastPosition=image->GetPosition();
	iImageLastSize=image->GetSize();
}
/**
default layout aligmnment 
1/align image to workspace borders
2/align image to other images in workspace
*/
void CFreeLayout::ImageResized(CImage *image)
{
	ImageResizedAlignToWorkspace(image);
	ImageResizedAlignToOtherImages(image);

}


