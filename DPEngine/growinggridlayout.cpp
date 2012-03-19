#include <growingGridLayout.h>
#include <cimage.h>
#include <cworkspace.h>

CGrowingGridLayout::CGrowingGridLayout(CWorkspace *parentWorkspace, TGrowingGridLayoutType type)
{
	iType = type;
	iParentWorkspace = parentWorkspace;
	iToSwap = false;
	iSwappedImage=NULL;
	iColumnCount=1;
	iRowCount=0;
	iLastUsedRow=0;
	iLastUsedColumn=0;
	//iLastDirection=EGrowingColumn;
	for(int i=0;i<EMaximumGridLayoutRowCount;i++)
	{
		for(int j=0;j<EMaximumGridLayoutRowCount;j++)
		{
			iImageGrid[i][j]=NULL;
		}
		iRowsHeights[i] = 0;
		iColumnWidths[i] = 0;
		iRowsTops[i] = 0;
		iColumnLefts[i] = 0;
	}
}
TLayoutType CGrowingGridLayout::GetType()
{
	if(iType == EGrowinGridLayoutHorizontal)
	{
	return ELayoutGrowingGridHorizontal;
	}
	else
		return ELayoutGrowingGridVertical;
}

CGrowingGridLayout::~CGrowingGridLayout()
{

}
void CGrowingGridLayout::Do()
{
	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	CImage *im;
	images.toFront();
	int count=0;
	iRowCount=0;
	iColumnCount = 0;
	if(iType == EGrowinGridLayoutHorizontal)
	{
		iRowCount = 1;
	}
	else
	{
		iColumnCount =1;
	}

	int capacity=iRowCount*iColumnCount;
	while(iParentWorkspace->GetImages().count()>capacity)
	{
		//prepare grid
		if(iType == EGrowinGridLayoutVertical)
		{
			if(iColumnCount<=iRowCount)
			{
				iColumnCount++;
			}
			else
			{
				iRowCount++;
			}
		}
		else
		{
			if(iRowCount<=iColumnCount)
			{
				iRowCount++;

			}
			else
			{
				iColumnCount++;
			}
		}
		capacity=iRowCount*iColumnCount;

	}
	if(iColumnCount==0 || iRowCount==0)
	{
		return;
	}
	//adjust already added images to new grid layout
	QPoint defaultSize=GetDefaultSize(iRowCount, iColumnCount);
	for(int j=0;j<iRowCount;j++)
	{
		iRowsHeights[j]=0;
		iColumnWidths[j]=0;
		iRowsTops[j]=0;
		iColumnLefts[j]=0;
		iRowsHeights[j]=defaultSize.y();
		iRowsTops[j]=defaultSize.y()*j+iParentWorkspace->GetBorders().top;
		for(int i=0;i<iColumnCount;i++)
		{
			iImageGrid[i][j] = NULL;
			iColumnWidths[i]=defaultSize.x();
			iColumnLefts[i]=defaultSize.x()*i+iParentWorkspace->GetBorders().left;
			if(images.hasNext())
			{
				im=images.next();
				iImageGrid[i][j]=im;
				float zoom = (float)iParentWorkspace->GetSize().x()/(float)im->GetTexture()->GetWidth();
				zoom/=iColumnCount;
				im->SetPosition(QPoint(
					iColumnLefts[i],
					iRowsTops[j]));
				im->SetSize(defaultSize);
			}
		}
	}




}

void CGrowingGridLayout::RemoveImage(CImage *image)
{
	for(int j=0;j<iRowCount;j++)
	{
		for(int i=0;i<iColumnCount;i++)
		{

			if(iImageGrid[i][j] == image)
			{
				iImageGrid[i][j]=NULL;
			}
		}
	}

	for(int x = iColumnCount-1;x>=0;x--)
	{
		bool bRemoveColumn=true;
		for (int y=0;y<iRowCount;y++)
		{
			if(iImageGrid[x][y]!=NULL)
			{
				bRemoveColumn = false;
				break;
			}
		}
		if(!bRemoveColumn)
		{
			break;
		}
		if(bRemoveColumn && iColumnCount>1)
		{
			iColumnCount--;
		}
	}

	for(int y=iRowCount-1;y>=0;y--)
	{
		bool bRemoveRow=true;
		for (int x=0;x<iColumnCount;x++)
		{
			if(iImageGrid[x][y]!=NULL)
			{
				bRemoveRow = false;
				break;
			}
		}
		if(!bRemoveRow)
		{
			break;
		}
		if(bRemoveRow && iRowCount>0)
		{
			iRowCount--;
		}
	}


//TODO lblImageRemoved:;
}

QPoint CGrowingGridLayout::GetDefaultSize(int rows, int columns)
{
	QPoint defaultSize((iParentWorkspace->GetSize().x()-iParentWorkspace->GetBorders().left-iParentWorkspace->GetBorders().right)
		/iColumnCount,
		(iParentWorkspace->GetSize().y()-iParentWorkspace->GetBorders().top-
		iParentWorkspace->GetBorders().bottom)/iRowCount);
	return defaultSize;
}
/**
* System of adding rows and columns to grid
*	1/ start with 1 column and 0 rows	
*	2/ add row
*	3/ fill grid with images
*	4/ add column
*	5/ fill with images
*	6/ step to number 2/
* return false if image can not be added
*/
bool CGrowingGridLayout::PrepareNewImageGeometry(CImage *image)
{

	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	CImage *im;

	int count=iParentWorkspace->GetImages().count();

	int capacity=iRowCount*iColumnCount;

	if(count>capacity)
	{
		//prepare grid
		if(iType == EGrowinGridLayoutVertical)
		{
			if(iColumnCount<=iRowCount)
			{
				iColumnCount++;
			}
			else
			{
				iRowCount++;
			}
		}
		else
		{
			if(iRowCount<=iColumnCount)
			{
				iRowCount++;
			}
			else
			{
				iColumnCount++;
			}
		}
		//adjust already added images to new grid layout
		images.toFront();
		if(iColumnCount>EMaximumGridLayoutRowCount | iRowCount>EMaximumGridLayoutRowCount)
		{
			return false;
		}

		QPoint defaultSize = GetDefaultSize(iRowCount, iColumnCount);



		for(int j=0;j<iRowCount;j++)
		{
			iRowsHeights[j]=0;
			iColumnWidths[j]=0;
			iRowsTops[j]=0;
			iColumnLefts[j]=0;
			iRowsHeights[j]=defaultSize.y();
			iRowsTops[j]=defaultSize.y()*j+iParentWorkspace->GetBorders().top;
			for(int i=0;i<iColumnCount;i++)
			{
				iImageGrid[i][j] = NULL;
				iColumnWidths[i]=defaultSize.x();
				iColumnLefts[i]=defaultSize.x()*i+iParentWorkspace->GetBorders().left;

				if(images.hasNext())
				{
					im=images.next();

					iImageGrid[i][j]=im;
					float zoom = (float)defaultSize.x()/(float)im->GetTexture()->GetWidth();
					zoom/=iColumnCount;
					im->SetZoom(zoom);
					im->SetPosition(QPoint(
						iColumnLefts[i],
						iRowsTops[j]));
					im->SetSize(defaultSize);
				}
			}
		}
		return true;
	}

	//add image to already prepared grid
	for(int j=0;j<iRowCount;j++)
	{
		for(int i=0;i<iColumnCount;i++)
		{
			if(iImageGrid[i][j] == NULL)
			{
				im=image;
				QPoint defaultPosition(
					iColumnLefts[i],
					iRowsTops[j]);
				QPoint defaultSize(
					iColumnWidths[i],
					iRowsHeights[j]);
				//	iColumnWidths[i]=defaultSize.x();
				//	iColumnLefts[i]=defaultSize.x()*i;
				im->SetPosition(defaultPosition);
				im->SetSize(defaultSize);
				iImageGrid[i][j]=im;
				float zoom = (float)iParentWorkspace->GetSize().x()/(float)im->GetTexture()->GetWidth();

				zoom/=iColumnCount;
				im->SetZoom(zoom);
				goto lblImageAdded;
			}



		}

	}
lblImageAdded:;
	return true;

}



void CGrowingGridLayout::PrepareImageToResize(CImage *image)
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
void CGrowingGridLayout::ImageResized(CImage *image)
{
	ImageResizedAlignToWorkspace(image);
	ResizeImagesOnRowAndColumn(image);
	//ImageResizedAlignToOtherImages(image);

}
/**
/*         Adjust sizes of images in the same row and column acording tu new size of image                                                             
*/
void CGrowingGridLayout::ResizeImagesOnRowAndColumn(CImage* image)
{
	//identify row and column of actual image
	int row=0,column=0;
	for (int i=0;i<iColumnCount;i++)
	{
		for (int j=0;j<iRowCount;j++)
		{

			if(iImageGrid[i][j] == image)
			{
				row=j;column=i;
				goto lblRowColumnIdentificationCompleted;
			}
		}

	}
	return;
	//adjust sizes for whole rows and column on the same row and columns
lblRowColumnIdentificationCompleted:;
	QPointF sizeLimit=iParentWorkspace->GetSize()-image->GetPosition();
	if(column<iColumnCount-1)
	{
		sizeLimit.setX(
			iColumnLefts[column+1]+iColumnWidths[column+1]-
			image->GetPosition().x()-25);
	}
	if(row<iRowCount-1)
	{
		sizeLimit.setY(iRowsTops[row+1]+iRowsHeights[row+1]-
			image->GetPosition().y()-25);
	}
	iColumnWidths[column] = sizeLimit.x();
	if(image->GetSize().x()<sizeLimit.x())
	{
		iColumnWidths[column] = image->GetSize().x();
	}
	iRowsHeights[row] =sizeLimit.y();
	if(image->GetSize().y()<sizeLimit.y())
	{
		iRowsHeights[row] = image->GetSize().y();
	}
	if(iColumnWidths[column] <25)
	{
		iColumnWidths[column] =25;
	}
	if(iRowsHeights[row] <25)
	{
		iRowsHeights[row] =25;
	}
	//adjust neighborhoods positions 
	if(column<iColumnCount-1)
	{
		int lastRight=iColumnLefts[column+1]+iColumnWidths[column+1];
		iColumnLefts[column+1]=iColumnLefts[column]+iColumnWidths[column];
		iColumnWidths[column+1]=lastRight-	iColumnLefts[column+1];
	}
	if(row<iRowCount-1)
	{
		int lastBottom=iRowsTops[row+1]+iRowsHeights[row+1];
		iRowsTops[row+1]=iRowsTops[row]+iRowsHeights[row];
		iRowsHeights[row+1]=lastBottom-	iRowsTops[row+1];
	}


	FitToGrid();

}


void CGrowingGridLayout::PrepareImageToMove(CImage *image)
{
	iCurrentImage = image;//being moved resized
	iImageLastPosition=image->GetPosition();
	iImageLastSize=image->GetSize();
	iSwappedImage=NULL;
}
/**
* -1,-1 signalize not found
*/
QPoint CGrowingGridLayout::FindGridPosition(CImage *image)
{
	QPoint gridPos(-1,-1);
	for (int i=0;i<iColumnCount;i++)
	{
		for (int j=0;j<iRowCount;j++)
		{
			QPoint gridPosCoords(iColumnLefts[i],iRowsTops[j]);
			if(gridPosCoords==image->GetPosition())
			{
				gridPos.setX(i);
				gridPos.setY(j);
			}
			/*if(iImageGrid[i][j]==image)
			{
			gridPos.setX(i);
			gridPos.setY(j);
			}*/
		}
	}


	return gridPos;
}
/**
default layout aligmnment 
1/align image to workspace borders
2/align image to other images in workspace
*/
void CGrowingGridLayout::ImageMoved(CImage *image)
{
//TODO	image->SetManipulated(EManipDissalowed);
	//ImageMovedAlignToWorkspace(image);
	ImageMovedAlignToOtherImages(image);
	QPointF imageCurrentPos = image->GetPosition();
	QPointF imageCurrentSize = image->GetSize();
	//check image coords with other - towards to swap them
	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	CImage *im;
	static QPoint gridFromPos,gridToPos;//position to swap

	if(iToSwap)
	{
		//return back to initial coords

		if(iSwappedImage != image && iSwappedImage!=NULL)
		{
//TODO			iSwappedImage->SetManipulated(EManipNone);
		}

		iImageGrid[gridToPos.x()][gridToPos.y()]=iSwappedImage;
		iImageGrid[gridFromPos.x()][gridFromPos.y()]=image;
	}
	iSwappedImage = NULL;

	FitToGrid();
	gridFromPos = FindGridPosition(image);
	//set back current image coords
	image->SetPosition(imageCurrentPos);
	//image->SetSize(imageCurrentSize);
	gridToPos.setX(-1);
	while(images.hasNext())
	{
		im=images.next();
		if((im!=image) && (im->GetPosition()==image->GetPosition()))
		{
			im->SetManipulated(EManipAllowed);
			iSwappedImage=im;
			gridToPos = FindGridPosition(im);
			break;
		}
	}
	if(gridToPos.x()==-1)
	{
		gridToPos = FindGridPosition(image);
		iSwappedImage=NULL;
	}

	iToSwap=false;
	//swap
	if(gridToPos.x()!=-1 && gridToPos != gridFromPos)
	{
		image->SetManipulated(EManipAllowed);
		iToSwap=true;
		iImageGrid[gridToPos.x()][gridToPos.y()]=image;
		iImageGrid[gridFromPos.x()][gridFromPos.y()]=iSwappedImage;
		//fit images to positions
		FitToGrid();

	}

}

void CGrowingGridLayout::FitToGrid()
{
	for(int j=0;j<iRowCount;j++)
	{
		for(int i=0;i<iColumnCount;i++)
		{
			if(iImageGrid[i][j] != NULL)
			{
				QPoint defaultPosition(
					iColumnLefts[i],
					iRowsTops[j]);
				QPoint defaultSize(
					iColumnWidths[i],
					iRowsHeights[j]);
				iImageGrid[i][j]->SetPosition(defaultPosition);
				iImageGrid[i][j]->SetSize(defaultSize);
			}
		}
	}
}
/**
* Called after user releaser mouse after moving object
*/
void CGrowingGridLayout::ImageMoveFinished(CImage *image)
{
	if(iSwappedImage)
	{
//TODO		iSwappedImage->SetManipulated(EManipNone);
	}
	iSwappedImage = NULL;
	iToSwap =false;
	FitToGrid();
	return;
	//ImageMovedAlignToWorkspace(image);
	ImageMovedAlignToOtherImages(image);
	QPointF imageCurrentPos = image->GetPosition();
	QPointF imageCurrentSize = image->GetSize();
	//return back to initial coords
	FitToGrid();
	QPoint gridFromPos=FindGridPosition(image);
	//return back to current coords
	image->SetPosition(imageCurrentPos);
	image->SetSize(imageCurrentSize);
	QPoint gridToPos(-1,0);
	gridToPos = FindGridPosition(image);


	QListIterator<CImage*> images(iParentWorkspace->GetImages());
	CImage *swappedImage=NULL;
	while(images.hasNext())
	{
		CImage *im=images.next();
		if((im!=image) && (im->GetPosition()==image->GetPosition()))
		{
//TODO			im->SetManipulated(EManipNone);
			swappedImage = im;
			//gridToPos = FindGridPosition(im);
			break;
		}
	}

	//swap
	if(gridToPos.x()!=-1)
	{
		iImageGrid[gridFromPos.x()][gridFromPos.y()]=swappedImage;
		iImageGrid[gridToPos.x()][gridToPos.y()]=image;

	}
	//fit images to positions
	FitToGrid();
}
